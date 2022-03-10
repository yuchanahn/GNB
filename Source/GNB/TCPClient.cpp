// Fill out your copyright notice in the Description page of Project Settings.
#include "TCPClient.h"
#include "GNBGameModeBase.h"

#include "YCNW/yc_client.hpp"
#include "../../../GNBServer/inc/packet/packet_data.hpp"

template <typename T>
void send(T& t, yc::byte_t buf[1024], yc::socket_t socket)
{
	auto len = ((packet_t<T>*) & t)->pack((unsigned char*)buf);
	::send(socket, (const char*)buf, len, 0);
}

TCPClient::TCPClient()
{
	clnt = new yc_client();
}

TCPClient::~TCPClient()
{
	closesocket(clnt->get_socket());
	th->join();
	delete th;
	delete clnt;
}

void TCPClient::ConnectServer(std::string ip, int port)
{
	packet_data_load();

	clnt->connect(ip.c_str(), port);

	yc_net::bind_ev<p_chat_message_t>([&](p_chat_message_t* chat, auto) {
		FString msg = chat->msg;
		auto self = game_mode;
		game_mode->jobs.enqueue([self, msg]{
			self->ChattingEvent.Broadcast(FChatMessage{ msg });
			});
		});

	yc_net::bind_ev<p_gacha_result_t>([&](p_gacha_result_t* r, auto) {
		auto gm = game_mode;
		FGachaResult rr;
		for (int i = 0; i < r->size; i++) rr.r.Add(static_cast<int32>(r->r[i]));
		game_mode->jobs.enqueue([gm, rr] {
			gm->GachaEvent.Broadcast(rr);
			});
		});

	th = new std::thread([&] {
		while (1)
		{
			int rt = clnt->read_packet();
			if (rt == -1) break;			// error
			else if (rt == 0) break;		// disconnect!
		}
		delete th;
		delete clnt;
		});
}

void TCPClient::SendChatting(std::wstring msg)
{
	p_chat_message_t p{  };
	std::copy(msg.begin(), msg.end(), p.msg);
	send(p, buf, clnt->get_socket());
}

void TCPClient::GachaStart(char cnt)
{
	p_gacha_start_t p{ cnt };
	send(p, buf, clnt->get_socket());
}
