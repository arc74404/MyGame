macro(get_sources SOURCE_LIST DIR)
    set(FOLDER_NAMES app dropped_object gui player world physical_object storage save)
    add_sources(${SOURCE_LIST} "${DIR}/sources" "${FOLDER_NAMES}")
endmacro()