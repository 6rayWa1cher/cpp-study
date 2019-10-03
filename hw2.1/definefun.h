//
// Created by Konstantin Grigoriev on 13/09/2019.
//

#ifndef EDUSANDBOX_DEFINEFUN_H
#define EDUSANDBOX_DEFINEFUN_H

#define getMax(a, b) ((a) > (b) ? (a) : (b))

#define brokenGetMax(a, b) a > b ? a : b
#ifdef NDEBUG
#define isDebug() (false)
#else
#define isDebug() (true)
#endif
#endif //EDUSANDBOX_DEFINEFUN_H
