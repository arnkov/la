#pragma once

#include <stdio.h>
#include <stdarg.h>

enum LogLevel {
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
};

static enum LogLevel gLogLevel = LOG_INFO;

static inline void laLogTrace(const char* format, ...) {
    if (gLogLevel <= LOG_TRACE) {
        va_list args;
        va_start(args, format);
        printf("[TRACE] ");
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }
}

static inline void laLogDebug(const char* format, ...) {
    if (gLogLevel <= LOG_DEBUG) {
        va_list args;
        va_start(args, format);
        printf("[DEBUG] ");
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }
}

static inline void laLogInfo(const char* format, ...) {
    if (gLogLevel <= LOG_INFO) {
        va_list args;
        va_start(args, format);
        printf("[INFO] ");
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }
}

static inline void laLogWarn(const char* format, ...) {
    if (gLogLevel <= LOG_WARN) {
        va_list args;
        va_start(args, format);
        fprintf(stderr, "[WARN] ");
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
        va_end(args);
    }
}

static inline void laLogError(const char* format, ...) {
    if (gLogLevel <= LOG_ERROR) {
        va_list args;
        va_start(args, format);
        fprintf(stderr, "[ERROR] ");
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
        va_end(args);
    }
}

static inline void laLogFatal(const char* format, ...) {
    if (gLogLevel <= LOG_FATAL) {
        va_list args;
        va_start(args, format);
        fprintf(stderr, "[FATAL] ");
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
        va_end(args);
    }
}

static inline void laSetLogLevel(enum LogLevel level) {
    gLogLevel = level;
}