{
    "targets": [{
        "target_name": "onitama",
        "include_dirs" : [
            "<!(node -e \"require('nan')\")",
            "source/onitama"
        ],
        "sources": [
            "source/onitama/index.cc"
        ]
    }]
}