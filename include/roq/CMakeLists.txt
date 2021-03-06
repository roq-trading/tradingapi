set(TARGET_NAME "${PROJECT_NAME}-include-cpp")

set(TARGET_DIR "${CMAKE_INSTALL_INCLUDEDIR}/roq")

set(SOURCES
    batch_begin.json
    batch_end.json
    cancel_all_orders.json
    cancel_order.json
    connected.json
    connection_status.json
    create_order.json
    disconnected.json
    download_begin.json
    download_end.json
    error.json
    execution_instruction.json
    external_latency.json
    fill.json
    funds_update.json
    gateway_settings.json
    gateway_status.json
    layer.json
    liquidity.json
    market_by_order_update.json
    market_by_price_update.json
    market_status.json
    mbo_update.json
    mbp_update.json
    message_info.json
    modify_order.json
    option_type.json
    order_ack.json
    order_cancel_policy.json
    order_management.json
    order_status.json
    order_type.json
    order_update.json
    order_update_action.json
    origin.json
    position_effect.json
    position_update.json
    priority.json
    rate_limit_usage.json
    reference_data.json
    request_status.json
    request_type.json
    security_type.json
    side.json
    start.json
    statistics.json
    statistics_type.json
    statistics_update.json
    stop.json
    stream_status.json
    stream_type.json
    support_type.json
    time_in_force.json
    timer.json
    top_of_book.json
    trade.json
    trade_summary.json
    trade_update.json
    trading_status.json)

# configure

set(API_H "${CMAKE_BINARY_DIR}/${TARGET_DIR}/api.h")

configure_file("api.h.in" "${API_H}" @ONLY)

# auto-generate

unset(AUTOGEN_HEADERS)

foreach(path ${SOURCES})
  set(source "${SCHEMA_DIR}/cpp/${path}")
  get_filename_component(name ${path} NAME_WE)
  set(target "${CMAKE_BINARY_DIR}/${TARGET_DIR}/${name}.h")
  add_custom_command(
    OUTPUT "${target}"
    COMMAND ${PYTHON_EXECUTABLE} "${AUTOGEN_PY}" --namespace "roq" --file-type "h" "${source}" >
            "${target}"
    COMMAND ${CLANG_FORMAT} -i "${target}"
    VERBATIM
    DEPENDS "${PYTHON_EXECUTABLE}" "${AUTOGEN_PY}" "${source}")
  list(APPEND AUTOGEN_HEADERS "${target}")
endforeach()

# target

add_custom_target("${TARGET_NAME}" ALL DEPENDS ${AUTOGEN_HEADERS} "${GITIGNORE}")

# install

install(FILES ${AUTOGEN_HEADERS} "${API_H}" DESTINATION "${TARGET_DIR}")
