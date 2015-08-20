//
// test.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 23 22:00:09 2015 alexis mestag
// Last update Wed May  6 20:03:05 2015 alexis mestag
//

#include		<iostream>
#include		"Entities/Week.hh"

int			main() {
  Week::Point		p(Week::Day::Monday, 3600);

  p = Week::Point(Week::Day::Tuesday, 7200);
  return (0);
}
