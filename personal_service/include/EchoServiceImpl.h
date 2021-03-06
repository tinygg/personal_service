#pragma once

#include <butil/logging.h>
#include <brpc/server.h>
#include "echo.pb.h"

namespace personal
{
	class EchoServiceImpl :public EchoService
	{
	public:
		EchoServiceImpl() {};
		virtual ~EchoServiceImpl() {};
		void virtual Echo(::google::protobuf::RpcController* cntl_base,
			const ::EchoRequest* request,
			::EchoResponse* response,
			::google::protobuf::Closure* done);
	};
}