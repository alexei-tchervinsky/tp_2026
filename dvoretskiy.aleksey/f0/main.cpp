#include "MenuRBTree.hpp"

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

int main()
{
#ifdef _WIN32
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
#endif

  RBTree tree;

  while (true)
  {
    std::cout
      << "1 - RBTree\n"
      << "0 - Exit\n";

    const int option =
      GetElementConsoleRBTree();

    if (option == 1)
    {
      Menu(&tree);
    }
    else if (option == 0)
    {
      FreeTree(tree.Root);
      return 0;
    }
    else
    {
      std::cout << "Invalid value.\n";
    }
  }
}
