/*
    Binance API Wrapper for C++
    
    Copyright (c) 2022 Hsin-Hung <https://github.com/Hsin-Hung>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

            http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */

#include "binanceWebsocket.h"

using namespace Binance;

BinanceWebsocket::BinanceWebsocket() : ctx{ssl::context::tlsv12_client}
{
    connectWebSocket();
}

void BinanceWebsocket::connectWebSocket()
{

    // The SSL context is required, and holds certificates
    // ssl::context ctx{ssl::context::tlsv12_client};

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws = std::make_shared<session>(ioc, ctx);
    ws->init(WS_BASE_ENDPOINT, WS_PORT);

    // Run the I/O service. The call will return when
    // the socket is closed.
}

void BinanceWebsocket::Run()
{

    auto work = boost::asio::require(ioc.get_executor(),
                                     boost::asio::execution::outstanding_work.tracked);
    ioc.run();
}
void BinanceWebsocket::SubscribeStreams(std::vector<std::string> streams, stream_callback callback)
{

    std::string path = "/stream";

    json j;
    j["method"] = "SUBSCRIBE";
    j["params"] = streams;
    j["id"] = 1;

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), j, callback);
}

void BinanceWebsocket::UnsubscribeStreams(std::vector<std::string> streams, stream_callback callback)
{
    std::string path = "/stream";

    json j;
    j["method"] = "UNSUBSCRIBE";
    j["params"] = streams;
    j["id"] = 2;

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), j, callback);
}
void BinanceWebsocket::ListSubscribtions(stream_callback callback)
{

    std::string path = "/stream";

    json j;
    j["method"] = "LIST_SUBSCRIPTIONS";
    j["id"] = 3;

    // The SSL context is required, and holds certificates
    ssl::context ctx{ssl::context::tlsv12_client};

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), j, callback);
}

void BinanceWebsocket::AccessCombinedStreams(std::vector<std::string> streams, stream_callback callback)
{
    std::string path = "/stream?streams=";
    for (auto i = 0; i < streams.size(); ++i)
    {

        path += streams[i];

        if (i != streams.size() - 1)
        {
            path += "/";
        }
    }

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}

void BinanceWebsocket::StreamAggregateTrade(std::string symbol, stream_callback callback)
{
    std::string path = "/ws/" + symbol + "@aggTrade";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}

void BinanceWebsocket::StreamTrade(std::string symbol, stream_callback callback)
{

    std::string path = "/ws/" + symbol + "@trade";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}
void BinanceWebsocket::StreamKlineCandlestick(std::string symbol, KCChartIntervals interval, stream_callback callback)
{

    std::string path = "/ws/" + symbol + "@kline_" + get_KCChartIntervals(interval);

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}
void BinanceWebsocket::StreamMiniTicker(std::string symbol, stream_callback callback)
{

    std::string path = "/ws/" + symbol + "@miniTicker";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}
void BinanceWebsocket::StreamAllMiniTickers(stream_callback callback)
{

    std::string path = "/ws/!miniTicker@arr";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}
void BinanceWebsocket::StreamSymbolTicker(std::string symbol, stream_callback callback)
{

    std::string path = "/ws/" + symbol + "@ticker";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}
void BinanceWebsocket::StreamAllMarketTickers(stream_callback callback)
{

    std::string path = "/ws/!ticker@arr";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}
void BinanceWebsocket::StreamSymbolBookTicker(std::string symbol, stream_callback callback)
{
    std::string path = "/ws/" + symbol + "@bookTicker";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}
void BinanceWebsocket::StreamAllBookTickers(stream_callback callback)
{

    std::string path = "/ws/!bookTicker";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}

void BinanceWebsocket::StreamPartialBookDepth(std::string symbol, std::string levels, bool updateSpeed, stream_callback callback)
{

    std::string path = "/ws/" + symbol + "@depth" + levels;
    if (updateSpeed)
        path += "@100ms";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}
void BinanceWebsocket::StreamDiffDepth(std::string symbol, bool updateSpeed, stream_callback callback)
{

    std::string path = "/ws/" + symbol + "@depth";
    if (updateSpeed)
        path += "@100ms";

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}

void BinanceWebsocket::StreamUserData(std::string key, stream_callback callback)
{

    std::string path = "/ws/" + key;

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);
    // Launch the asynchronous operation
    ws->run(path.c_str(), json(), callback);
}
