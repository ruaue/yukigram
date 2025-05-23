/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "base/weak_ptr.h"
#include "mtproto/mtproto_dedicated_loader.h"

#include <rpl/producer.h>

namespace Main {
class Session;
} // namespace Main

namespace Core {

class Updater;

class UpdateChecker {
public:
	UpdateChecker();
	~UpdateChecker();

	rpl::producer<> checking() const;
	rpl::producer<> isLatest() const;
	rpl::producer<MTP::AbstractDedicatedLoader::Progress> progress() const;
	rpl::producer<> failed() const;
	rpl::producer<> ready() const;

	void start(bool mtproto = false);
	void test();
	void setMtproto(base::weak_ptr<Main::Session> session);
	void stop();

	enum class State {
		Checking,
		Latest,
		Downloading,
		Ready,
		Failed,
	};
	[[nodiscard]] State state() const;
	[[nodiscard]] int already() const;
	[[nodiscard]] int size() const;

private:
	std::shared_ptr<Updater> _impl;

};

[[nodiscard]] bool IsAppLaunched();
void UpdateApplication();

} // namespace Core
