#!/usr/bin/env python3
import os
import re
import sys

# Set base dir for the files as global var
SRC_DIR_REL = "develop/global/src"


def update_file_version(file_path, pattern, new_version):
    """
    Reads a file, updates the version number based on regex, and saves it.
    """
    if not os.path.isfile(file_path):
        print(f"Error: Target file missing: {file_path}", file=sys.stderr)
        sys.exit(1)

    # Ensure writable permissions
    os.chmod(file_path, 0o755)

    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    # Match the variable name, any spacing around '=', and the digits
    regex_pattern = rf"({pattern}\s*=\s*)\d+"
    
    if not re.search(regex_pattern, content):
        print(f"Warning: Match pattern for '{pattern}' not found in {os.path.basename(file_path)}")
        return

    # Use backreference \1 to keep everything before the digits intact
    updated_content = re.sub(regex_pattern, rf"\1{new_version}", content)

    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(updated_content)

    print(f"Successfully updated version in {os.path.basename(file_path)}")


def main():
    # Fetch and validate env setup
    source_path = os.environ.get("SourcePath")
    build_num = os.environ.get("BuildNum")

    if not source_path or not build_num:
        print("Error: Environment variables 'SourcePath' or 'BuildNum' are not set.", file=sys.stderr)
        sys.exit(1)

    target_dir = os.path.join(source_path, SRC_DIR_REL)

    # Map the files to their respective configuration keywords
    targets = {
        "SConstruct": "point",
        "VERSION": "ADLMSDK_VERSION_POINT"
    }

    print(f"Updating build version to: {build_num}")
    
    # Iterate through target items 
    for filename, pattern in targets.items():
        full_path = os.path.join(target_dir, filename)
        update_file_version(full_path, pattern, build_num)


if __name__ == "__main__":
    main()