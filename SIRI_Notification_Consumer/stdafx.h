// stdafx.h: archivo de inclusi�n de los archivos de inclusi�n est�ndar del sistema
// o archivos de inclusi�n espec�ficos de un proyecto utilizados frecuentemente,
// pero rara vez modificados

#pragma once

#ifdef _WIN32

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Excluir material rara vez utilizado de encabezados de Windows
#endif

#include "targetver.h"

// Archivos de encabezado de Windows:
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <TCHAR.h>
#include <codecvt>

#pragma warning(disable:4251)
#pragma warning(disable:4275)

#define SIRI_SAER_API

#else //GCC

#define LPCTSTR const char*
#define LPCSTR const char*
#define LPTSTR char*
#define LPSTR char*
#define TCHAR char
#define _T(x) x
#define _tcslen strlen
#define _countof(T) sizeof(T)/sizeof(T[0])
#define _tcstol strtol
#define _isnan isnan
#define _tcstod_l strtod_l

#define SIRI_SAER_API __attribute__ ((visibility ("default")))

#endif

#include <stdint.h>
#include <string>
#include <sstream>
#include <boost/date_time.hpp>
#include <boost/format.hpp>

#ifdef UNICODE
typedef std::wstringstream _tstringstream;
typedef std::wstring _tstring;
typedef boost::posix_time::wtime_facet _boost_time_facet;
typedef boost::gregorian::wdate_facet _boost_date_facet;
typedef boost::wformat _boost_format;
typedef std::wofstream _ofstream;
#else
typedef std::stringstream _tstringstream;
typedef std::string _tstring;
typedef boost::posix_time::time_facet _boost_time_facet;
typedef boost::gregorian::date_facet _boost_date_facet;
typedef boost::format _boost_format;
typedef std::ofstream _ofstream;
#endif


//#include "../../SW_COMUN/Loger/StaticLog.h"
