#pragma once
#include <unordered_map>
#include "qnamespace.h"

class KeyboardTranslator
{
  public:
    static bool Translate(int winKey, Qt::Key& qtKey);
    static bool Translate(Qt::Key qtKey, int& winKey);

  private:
#ifdef Q_OS_WINDOWS
    static const std::unordered_map<Qt::Key, int> m_qtKey2WinKey;
    static const std::unordered_map<int, Qt::Key> m_winKey2QtKey;
#endif
};
