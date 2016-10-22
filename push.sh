#!/bin/bash

git add .
printf "Enter commit"
read -p ": " gCommit_Contents
git commit -m "$gCommit_Contents"
git push -u origin master

exit 0
