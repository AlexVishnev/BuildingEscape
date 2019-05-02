#pragma once

#ifndef DEFINES_HPP
#define DEFINE_HPP
#define OPENDOOR 1
#define CLOSEDOOR 0

#ifndef PRINT
# define PRINT(message) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT(message));
#endif // !1

#endif // !DEFINES_HPP