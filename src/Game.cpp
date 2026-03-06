#include "Game.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include <format>
#include <iostream>
#include <regex>

#include "Vector2.h"

Game::Game() : m_board{3, 3}
{
}

bool Game::ExtractCoordsFromString(const std::string& text, Vector2& out)
{
    const std::regex coordsPattern(R"(([0-9]+),([0-9]+))");
    std::smatch matches;

    if (!std::regex_match(text, matches, coordsPattern))
        return false;

    out.x = std::stof(matches[1]);
    out.y = std::stof(matches[2]);
    return true;
}

Vector2 Game::GetValidCoordsFromUser() const
{
    const std::string lineHeader = std::format("[P{}]", m_currentPlayer);
    const std::string prompt = "Enter coord (x,y):";

    auto RewriteLineWithError = [&](const std::string& reason) {
        RewriteLine(std::format("{} {}. {} ", lineHeader, reason, prompt));
    };

    std::cout << std::format("{} {} ", lineHeader, prompt);
    std::string userInput;

    while (true)
    {
        std::getline(std::cin, userInput);
        Vector2 extractedCoords;

        if (!ExtractCoordsFromString(userInput, extractedCoords))
        {
            RewriteLineWithError("Invalid input");
            continue;
        }

        extractedCoords -= Vector2{1, 1}; // To convert to 0 based index system

        if (!m_board.IsInBounds(extractedCoords))
        {
            RewriteLineWithError("Coords out of bounds");
            continue;
        }

        if (m_board.IsSpaceTaken(extractedCoords))
        {
            RewriteLineWithError("Space taken");
            continue;
        }

        return extractedCoords;
    }
}

void Game::Run()
{
    constexpr int maxTurns = 9;

    for (int turnCount = 0; turnCount < maxTurns; ++turnCount)
    {
        m_currentPlayer = (turnCount % 2) + 1;
        ClearScreen();
        m_board.PrintBoard();
        Vector2 coords = GetValidCoordsFromUser();
    }

}

void Game::ClearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    DWORD charsWritten;
    constexpr COORD originCoords = {0, 0};

    if (consoleHandle == INVALID_HANDLE_VALUE)
        return;

    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);
    const DWORD totalCells = screenBufferInfo.dwSize.X * screenBufferInfo.dwSize.Y;

    FillConsoleOutputCharacter(consoleHandle, ' ', totalCells, originCoords, &charsWritten);
    FillConsoleOutputAttribute(consoleHandle, screenBufferInfo.wAttributes, totalCells, originCoords, &charsWritten);
    SetConsoleCursorPosition(consoleHandle, originCoords);
#else
    std::fputs("\033[2J\033[H", stdout);
    std::fflush(stdout);
#endif
}

void Game::MoveCursorUp(int lineCount)
{
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);
    const COORD targetPos = {0, static_cast<short>(screenBufferInfo.dwCursorPosition.Y - lineCount)};
    SetConsoleCursorPosition(consoleHandle, targetPos);
#else
    std::cout << "\033[" << lineCount << "A";
#endif
}

void Game::ClearLine()
{
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);
    const COORD lineStartPos = {0, screenBufferInfo.dwCursorPosition.Y};
    DWORD charsWritten;
    FillConsoleOutputCharacter(consoleHandle, ' ', screenBufferInfo.dwSize.X, lineStartPos, &charsWritten);
    SetConsoleCursorPosition(consoleHandle, lineStartPos);
#else
    std::cout << "\033[2K";
#endif
}

void Game::RewriteLine(const std::string& newText)
{
    MoveCursorUp(1);
    ClearLine();
    std::cout << newText;
}
