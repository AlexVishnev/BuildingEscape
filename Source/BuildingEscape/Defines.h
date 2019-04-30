#pragma once

#ifndef DEFINES_HPP
#define DEFINE_HPP

#ifndef PRINT
# define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT(text));
#endif // !1

#endif // !DEFINES_HPP