# Check doxygen build log and display any errors or warnings.

message(STATUS "Checking for doxygen errors in ${logfile}")

file(READ "${logfile}" LOG)
string(LENGTH "${LOG}" LOGLEN)

if(LOGLEN GREATER 0)
    message(WARNING "Doxygen encountered undocumented code or errors in ${logfile}")
    message("══════════════════════════════ UNDOCUMENTED CODE ══════════════════════════════")
    message("${LOG}")
    message("═════════════════════════════ END UNDOCUMENTED CODE ═══════════════════════════")
endif()
