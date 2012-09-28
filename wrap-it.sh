#!/bin/bash
ctags *
git add .
git commit
md README.md -f README.html
git log --pretty=format:'%h, %ar, message: %s' > git-log
zip p1.zip            docs/* .git/* git-log *.h *.c mesh/* Makefile README.html
tar -z -cf p1.tar.gz  docs/  .git/  git-log *.h *.c mesh/  Makefile README.html

