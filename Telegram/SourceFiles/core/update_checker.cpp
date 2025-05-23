/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "core/update_checker.h"

#include "base/platform/base_platform_info.h"
#include "base/call_delayed.h"
#include "base/unixtime.h"
#include "main/main_domain.h"
#include "main/main_session.h"
#include "core/launcher.h"
#include "core/application.h"
#include "mtproto/mtproto_config.h"
#include "ui/boxes/confirm_box.h"
#include "ui/text/text_utilities.h"
#include "ui/toast/toast.h"
#include "lang/lang_keys.h"

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

namespace Core {
namespace {

constexpr auto kUpdaterTimeout = crl::time(3600'000) * 24;

} // namespace

UpdateChecker::UpdateChecker()
: _impl(std::make_shared<Updater>()) {
}

UpdateChecker::~UpdateChecker() = default;

rpl::producer<> UpdateChecker::checking() const {
	return _impl->checking();
}

rpl::producer<> UpdateChecker::isLatest() const {
	return _impl->isLatest();
}

rpl::producer<MTP::AbstractDedicatedLoader::Progress> UpdateChecker::progress() const {
	return _impl->progress();
}

rpl::producer<> UpdateChecker::failed() const {
	return _impl->failed();
}

rpl::producer<> UpdateChecker::ready() const {
	return _impl->ready();
}

void UpdateChecker::start(bool mtproto) {
	_impl->start(mtproto);
}

void UpdateChecker::test() {
	_impl->test();
}

void UpdateChecker::setMtproto(base::weak_ptr<Main::Session> session) {
	_impl->setMtproto(session);
}

void UpdateChecker::stop() {
	_impl->stop();
}

UpdateChecker::State UpdateChecker::state() const {
	return _impl->state();
}

int UpdateChecker::already() const {
	return _impl->already();
}

int UpdateChecker::size() const {
	return _impl->size();
}

bool IsAppLaunched() {
	return ::Core::App().domain().started();
}

void UpdateApplication() {
	if (!IsAppLaunched()) {
		return;
	}
	::Core::App().update();
}

} // namespace Core
