from pathlib import Path

# Directory to search (current directory)
directory = Path(".")

# Rename all .h files to .hpp
for file_path in directory.rglob("*.h"):
    new_path = file_path.with_suffix(".hpp")

    # Avoid overwriting existing files
    if new_path.exists():
        print(f"Skipped (already exists): {new_path}")
        continue

    file_path.rename(new_path)
    print(f"Renamed: {file_path} -> {new_path}")

print("Done.")