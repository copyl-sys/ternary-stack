#!/bin/bash

# === NIGHTSHIFT MEMORY PALACE (Legacy + Resume Explorer Edition) ===
# A terminal-based mnemonic interface to explore the life, mind, and work of Michael J. Kane II
# Designed for future generations, cybersecurity enthusiasts, and daughters seeking to understand their father.

# === ANSI Colors ===
reset=$'\e[0m'
purple=$'\e[35m'
blue=$'\e[34m'
green=$'\e[32m'
yellow=$'\e[33m'
red=$'\e[31m'
cyan=$'\e[36m'

# === Sync Mode: Journal Entry Logging ===
if [[ "$1" == "-sync" && -n "$2" ]]; then
  shift
  echo "$(date): $*" >> ./palace_journal.log
  echo "📝 Journal entry added to palace_journal.log"
  exit 0
fi

if [[ "$1" == "-async" && -n "$2" ]]; then
  shift
  echo "$(date): $*"
  echo "📝 Journal entry not added to palace_journal.log"
  exit 0
fi

# === Welcome ===
intro() {
  clear
  echo "${purple}╔════════════════════════════════════════════════════════╗"
  echo "║         NIGHTSHIFT MEMORY PALACE — FAMILY EDITION      ║"
  echo -e "╚════════════════════════════════════════════════════════╝${reset}"
  echo "This is a memory interface of your father, Skip."
  echo "Explore his life, experiences, and values. Type 'help' to begin."
}

help_menu() {
  echo ""
  echo "${cyan}Available paths in the palace:${reset}"
  echo "  enter east        → Legacy Tech & Data Systems"
  echo "  enter west        → Cybersecurity & Digital Defense"
  echo "  enter north       → Military & Communications"
  echo "  enter south       → Engineering & Industrial Work"
  echo "  enter vault       → Certifications & Core Beliefs"
  echo "  enter archive     → Logs, Field Records, & Reflections"
  echo "  enter observatory → Future Vision: Axion & AI Legacy"
  echo "  enter family      → Memories, Values, Lessons for My Daughters"
  echo "  view resume       → Print the full resume on-screen"
  echo "  quote toffler     → Alvin Toffler's guiding words"
  echo "  exit              → Leave the Memory Palace"
  echo ""
}

# === Memory Rooms ===
east_wing() {
  echo "${blue}\n🧰 EAST WING: LEGACY TECH\n${reset}- Learned COBOL, Java, and VisualBasic early on.
- Automated billing on AS/400 systems. Reverse engineered databases.
- Built tools before the cloud. Adapted when tech evolved.
- Echo: 'Legacy systems are still the veins of modern networks.'"
}

west_wing() {
  echo "${green}\n🛡 WEST WING: CYBER DEFENSE\n${reset}- Reverse engineering with Ghidra.
- Linux Kernel debugging and analytics.
- CISA-level aspirations fueled by real-world readiness.
- Echo: 'Cybersecurity is more than defense—it's resilience.'"
}

north_tower() {
  echo "${cyan}\n📡 NORTH TOWER: MILITARY LIFE\n${reset}- USAF Wireless Systems (2E611), comms and readiness.
- CBRN and Medic-X certified. Under 600v system installs.
- National Defense Service Medal.
- Echo: 'Discipline is the foundation of freedom.'"
}

south_wing() {
  echo "${yellow}\n🔩 SOUTH WING: HANDS-ON EXPERIENCE\n${reset}- Field-certified in hydraulics, logistics, and warehouse ops.
- Worked through fires, systems collapses, and built them back.
- Customer-first mentality and process-minded.
- Echo: 'Mastery is earned through labor, not luck.'"
}

vault_room() {
  echo "${purple}\n🔐 CENTRAL VAULT: CORE CERTIFICATIONS\n${reset}- MOS, CCNA, NCCER, Leviton Installer, Parker Hydraulic Tech.
- USAF 2E611 + National Defense Service Medal.
- Echo: 'Every certification, a step toward purpose.'"
}

archive_room() {
  echo "${red}\n🕳 ARCHIVE ROOM: FIELD RECORDS\n${reset}- Logs from Netcat sessions, AS/400 jobs, and support desks.
- 500+ users supported across 27 locations.
- Repaired, rebuilt, and documented every system touched.
- Echo: 'Logs are memory. Memory is resilience.'"
}

observatory() {
  echo "${purple}\n🧬 OBSERVATORY: FUTURE VISION\n${reset}- Axion: an AI package manager that learns.
- T81Lang: A ternary programming language born from curiosity.
- A vision for computing that integrates humanity.
- Echo: 'Think beyond binaries. Build what does not yet exist.'"
}

family_room() {
  echo "${green}\n💖 FAMILY ROOM: FOR MY DAUGHTERS\n${reset}- I built systems, but also built character.
- I worked odd jobs to pay bills, but always studied.
- I learned to unlearn, to survive, to evolve.
- You were always the reason I kept moving forward.
- Echo: 'Never fear the unknown. You carry my curiosity.'"
}

quote_toffler() {
  echo ""
  echo "${green}\"The illiterate of the 21st century will not be those who cannot read and write,"
  echo "but those who cannot learn, unlearn, and relearn.\""
  echo "    — Alvin Toffler${reset}"
  echo ""
}

view_resume() {
  echo "${cyan}\n=== FULL RESUME: MICHAEL J. KANE II ===${reset}"
  cat <<'EOF'
[Insert entire raw resume content here — .pdf converted to plain text.]
EOF
  echo "\n${cyan}=== END RESUME ===${reset}"
}

# === Command Loop ===
intro

while true; do
  read -e -p $'\e[34m🧠 > \e[0m' cmd
  case $cmd in
    "help") help_menu ;;
    "enter east") east_wing ;;
    "enter west") west_wing ;;
    "enter north") north_tower ;;
    "enter south") south_wing ;;
    "enter vault") vault_room ;;
    "enter archive") archive_room ;;
    "enter observatory") observatory ;;
    "enter family") family_room ;;
    "view resume") view_resume ;;
    "quote toffler") quote_toffler ;;
    "exit") echo "${cyan}Logging out of the Memory Palace... Stay curious.${reset}"; break ;;
    *) echo "${red}Command not recognized. Try 'help'.${reset}" ;;
  esac
done
