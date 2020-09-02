
#pragma once

#include "envoy/buffer/buffer.h"
#include "envoy/http/codes.h"
#include "envoy/http/header_map.h"
#include "envoy/server/admin.h"
#include "envoy/server/instance.h"

#include "server/admin/config_tracker_impl.h"
#include "server/admin/handler_ctx.h"

#include "absl/strings/string_view.h"

namespace Envoy {
namespace Server {

class ConfigDumpHandler : public HandlerContextBase {

public:
  ConfigDumpHandler(Server::Instance& server);

  Http::Code handlerConfigDump(absl::string_view path_and_query,
                               Http::ResponseHeaderMap& response_headers,
                               Buffer::Instance& response, AdminStream&) const;

private:
  void addAllConfigToDump(envoy::admin::v3::ConfigDump& dump,
                          const absl::optional<std::string>& mask, bool include_eds) const;
  /**
   * Add the config matching the passed resource to the passed config dump.
   * @return absl::nullopt on success, else the Http::Code and an error message that should be added
   * to the admin response.
   */
  absl::optional<std::pair<Http::Code, std::string>>
  addResourceToDump(envoy::admin::v3::ConfigDump& dump, const absl::optional<std::string>& mask,
                    const std::string& resource, bool include_eds) const;

  /**
   * Helper methods to add endpoints config
   */
  void addLbEndpoint(const Upstream::HostSharedPtr& host,
                     envoy::config::endpoint::v3::LocalityLbEndpoints& locality_lb_endpoint) const;

  ProtobufTypes::MessagePtr dumpEndpointConfigs() const;

  ConfigTrackerImpl config_tracker_;
};

} // namespace Server
} // namespace Envoy
