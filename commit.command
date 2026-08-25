#!/bin/zsh

# 1. Set your project repository directory
REPO_PATH="$HOME/Developer/micromouse"

cd "$REPO_PATH" || {
  osascript -e 'display alert "Error" message "Repository path not found."'
  exit 1
}

# 2. Open a native pop-up dialog to ask for the commit message
COMMIT_MSG=$(osascript -e '
  tell application "System Events"
    activate
    set response to display dialog "Enter your Git commit message:" default answer "" buttons {"Cancel", "Commit & Push"} default button "Commit & Push"
    return text returned of response
  end tell
')

# Exit if empty or canceled
if [ -z "$COMMIT_MSG" ]; then
  exit 0
fi

# 3. Add, Commit, and Push
git add .
git commit -m "$COMMIT_MSG"
PUSH_OUTPUT=$(git push 2>&1)

# 4. Show success or failure notification
if [ $? -eq 0 ]; then
  osascript -e "display notification \"Pushed successfully!\" with title \"Git Auto-Commit\""
else
  osascript -e "display alert \"Git Push Failed\" message \"$PUSH_OUTPUT\""
fi