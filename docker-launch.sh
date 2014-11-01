#!/bin/bash

set -e

# This script launches MaNGOS-Zero in a Docker container.
# If maps & DBCs have not been extracted yet it expects to find
# a copy of WoW mounted into /opt/mangos/wow to extract them.

readonly WOW_DIR="/opt/mangos/wow"
readonly DATA_DIR="/opt/mangos/data"

function check_dbc_and_maps() {
    if [ ! -d "${DATA_DIR}/dbc" ] || [ ! -d "${DATA_DIR}/maps" ]; then
        echo "Extracted data not found, proceeding with extraction"
        mkdir "${DATA_DIR}"
        extract_maps_dbc
        extract_assemble_vmaps
        generate_mmaps
    else
        echo "Extracted data present, proceeding to launch..."
    fi
}


function extract_maps_dbc() {
    /opt/mangos/bin/tools/map-extractor -i "${WOW_DIR}" -o "${DATA_DIR}"
}

function extract_assemble_vmaps() {
    cd "${DATA_DIR}"
    /opt/mangos/bin/tools/vmap-extractor -l -d "${WOW_DIR}"

    # Assemble vmaps
    mkdir "${DATA_DIR}/vmaps"
    /opt/mangos/bin/tools/vmap-assembler "${DATA_DIR}/Buildings" "${DATA_DIR}/vmaps"
}

function generate_mmaps() {
    cd "${DATA_DIR}"
    mkdir "${DATA_DIR}/mmaps"
    /opt/mangos/bin/tools/mmap-generator
}

function launch_realmd() {
    echo "Launching login server in background ..."
    /opt/mangos/bin/realmd -s run
}

function launch_mangosd() {
    echo "Launching world server ..."
    /opt/mangos/bin/mangosd
}

function run_mangos() {
    check_dbc_and_maps
    launch_realmd
    cd "${DATA_DIR}" && launch_mangosd    
}

run_mangos
