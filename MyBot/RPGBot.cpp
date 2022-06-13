#include <dpp/dpp.h>
#include <random>
#include <regex>

/* Be sure to place your token in the line below.
 * Follow steps here to get a token: https://dpp.dev/creating-a-bot-application.html
 * You will also need to fill in your guild id. When you invite the bot, be sure to
 * invite it with the scopes 'bot' and 'applications.commands', e.g.
 * https://discord.com/oauth2/authorize?client_id=940762342495518720&scope=bot+applications.commands&permissions=139586816064
 */
const std::string    BOT_TOKEN    = "OTgzODUwMDc2NzU5ODE4Mjcx.GKn8kr.OXequR4uJKjuuYuQAzTfeCN7G0zkFD3HZh6pnI";
const dpp::snowflake MY_GUILD_ID = 739430994276253707;
int* getInput(const std::string& s);
int main()
{
    /* Create bot cluster */
    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);
    std::random_device r;
    //std::regex p("![0-9]+d[0-9]+");

    /* Output simple log messages to stdout */ 
    bot.on_log(dpp::utility::cout_logger());
    //dpp::confirmation_callback_t c(&bot);
    //dpp::intents a = dpp::i_message_content;
    /* Handle input message */
    bot.on_message_create([&](const dpp::message_create_t& event) {
         if (std::regex_match(event.msg.content, std::regex("![0-9]+d[0-9]+"))) {
            std::string output = "";
            int* nums = getInput(event.msg.content);
            int times = nums[0];
            int sides = nums[1];
            std::uniform_int_distribution<int> dist(1, sides);
            //int* generated = new int[times];
            output += "[";
            for (int i = 0; i < times - 1; i++) {
                 //generated[i] = dist(r);
                 output += std::to_string(dist(r)) + ", ";
            }
            output += std::to_string(dist(r)) + "]";
            event.send(output);
        }
    });

    /* Register slash command here in on_ready */
    /*bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        /*if (dpp::run_once<struct register_bot_commands>()) {
            bot.guild_command_create(dpp::slashcommand("bing", "chilling!", bot.me.id), MY_GUILD_ID);
        }
    });*/

    /* Start the bot */
    bot.start(false);

    return 0;
}
int* getInput(const std::string& s) {
     int* arr = new int[2];
     std::size_t pos = s.find("d");
     arr[0] = std::stoi(s.substr(1, pos));
     arr[1] = std::stoi(s.substr(pos + 1));
     return arr;
}
