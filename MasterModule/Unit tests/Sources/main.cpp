//
// main.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Apr 14 17:43:40 2015 alexis mestag
// Last update Thu Jun 25 21:14:28 2015 alexis mestag
//

#include	<exception>
#include	<iostream>
#include	"UnitTestsClient.hh"

int		main() {
  int		ret = 0;

  try {
    UnitTestsClient	client("0.0.0.0", "4242");

    client.run();
  }
  catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
    ret = 1;
  }
  return (ret);
}
