import "pe"

rule brc4_core {
    meta:
        version = "1.3.x to 1.6.x BRc4 Releases"
        author = "Chetan Nayak (@ninjaparanoid)"
        date = "2024-07-02"
        description = "Detects every staged and stageless badger, on disk or in memory between the above mentioned releases"
        arch_context = "x64"
    strings:
        $hash1 = { 30 53 FA 0A }
        $hash2 = { 88 22 BA CE }
        $hash3 = { E6 23 FC 63 }
        $hash4 = { 96 FC 86 4B }
        $hash5 = { 74 BD 99 72 }
        $hash6 = { D2 94 94 26 }
        $hash7 = { 75 5F D2 66 }
        $hash8 = { 63 4F ED FB }
        $hash9 = { C8 85 E9 F6 }

    condition:
        any of ($hash*)
}