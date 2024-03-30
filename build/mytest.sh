## FAILED

# make
# ctest -R "fsm_stream_reassembler_cap"
# clear
# ctest -R "fsm_stream_reassembler_cap" --rerun-failed --output-on-failure

# make
# ctest -R "fsm_stream_reassembler_many"
# clear
# ctest -R "fsm_stream_reassembler_many" --rerun-failed --output-on-failure

## ALL

make
clear
ctest -R "^fsm_stream_reassembler"


## SUCCESS

# make
# ctest -R "fsm_stream_reassembler_dup"
# clear
# ctest -R "fsm_stream_reassembler_dup" --rerun-failed --output-on-failure

# make
# ctest -R "fsm_stream_reassembler_single"
# clear
# ctest -R "fsm_stream_reassembler_single" --rerun-failed --output-on-failure

# make
# ctest -R "fsm_stream_reassembler_overlapping"
# clear
# ctest -R "fsm_stream_reassembler_overlapping" --rerun-failed --output-on-failure

# make
# ctest -R "fsm_stream_reassembler_holes"
# clear
# ctest -R "fsm_stream_reassembler_holes" --rerun-failed --output-on-failure

# make
# ctest -R "fsm_stream_reassembler_win"
# clear
# ctest -R "fsm_stream_reassembler_win" --rerun-failed --output-on-failure
