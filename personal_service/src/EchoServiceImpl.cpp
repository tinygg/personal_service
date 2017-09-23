#include <butil/logging.h>
#include <brpc/server.h>
#include "echo.pb.h"
#include "EchoServiceImpl.h"

DEFINE_bool(echo_attachment, true, "Echo attachment as well");

void personal::EchoServiceImpl::Echo(::google::protobuf::RpcController* cntl_base,
	const ::EchoRequest* request,
	::EchoResponse* response,
	::google::protobuf::Closure* done)
{
	// This object helps you to call done->Run() in RAII style. If you need
	// to process the request asynchronously, pass done_guard.release().
	brpc::ClosureGuard done_guard(done);

	brpc::Controller* cntl =
		static_cast<brpc::Controller*>(cntl_base);

	// The purpose of following logs is to help you to understand
	// how clients interact with servers more intuitively. You should 
	// remove these logs in performance-sensitive servers.
	// You should also noticed that these logs are different from what
	// we wrote in other projects: they use << instead of printf-style
	// functions. But don't worry, these logs are fully compatible with
	// comlog. You can mix them with comlog or ullog functions freely.
	// The noflush prevents the log from being flushed immediately.
	LOG(INFO) << "Received request[log_id=" << cntl->log_id()
		<< "] from " << cntl->remote_side()
		<< " to " << cntl->local_side() << noflush;
	LOG(INFO) << ": " << request->message() << noflush;
	if (!cntl->request_attachment().empty()) {
		LOG(INFO) << " (attached=" << cntl->request_attachment() << ")" << noflush;
	}
	LOG(INFO);

	// Fill response.
	response->set_message(request->message());

	// You can compress the response by setting Controller, but be aware
	// that compression may be costly, evaluate before turning on.
	// cntl->set_response_compress_type(brpc::COMPRESS_TYPE_GZIP);

	if (FLAGS_echo_attachment) {
		// Set attachment which is wired to network directly instead of
		// being serialized into protobuf messages.
		cntl->response_attachment().append(cntl->request_attachment());
	}
}