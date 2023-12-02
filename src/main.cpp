#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/database.h>
#include <swiftly/commands.h>
#include <swiftly/configuration.h>
#include <swiftly/logger.h>
#include <swiftly/timers.h>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Database *db = nullptr;
Commands *commands = nullptr;
Configuration *config = nullptr;
Logger *logger = nullptr;
Timers *timers = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    commands = new Commands(pluginName);
    config = new Configuration();
    logger = new Logger(mainFilePath, pluginName);
    timers = new Timers();
}

void OnPluginStart()
{
}

void Timer()
{
    print("There are %02d players on the server.\n", g_playerManager->GetPlayers());
    timers->DestroyTimer(timerid);
}

void TimerCallback(int timerid, int remainingTime) {
    print("Remaining time: %d seconds\n", remainingTime);
}

void OnBombPlanted(Player *player, unsigned short site) {
    print("%s planted a bomb.\n", player->GetName());
    for (int i = 0; i < 40; i++) {
        timers->RegisterTimer(1000 * (i + 1), [i]() { TimerCallback(i, 40 - i); });
    }
}



void OnPluginStop()
{
    timers->UnregisterTimers();
}

const char *GetPluginAuthor()
{
    return "";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "c4timer";
}

const char *GetPluginWebsite()
{
    return "";
}