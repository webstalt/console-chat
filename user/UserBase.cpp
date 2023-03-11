#pragma once

#include "UserBase.h"

UserBase::~UserBase
{
  delete[] _users;
}