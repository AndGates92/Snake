#include <execinfo.h>
#include <cstring>

#include "trace_logging.h"


void trace_logging::print_backtrace(int file_descriptor) {

	void * trace[backtrace_entries];
	size_t trace_size = backtrace(trace, backtrace_entries);

	backtrace_symbols_fd(trace, trace_size, file_descriptor);
}
