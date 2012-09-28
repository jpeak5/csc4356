#!/bin/bash
ctags *
git add .
git commit
md README.md -f README.html
git log --pretty=format:'%h, %ar, message: %s' > git-log
zip output/p1.zip            docs/* .git/* git-log *.h *.c mesh/* Makefile README.html .gitignore
tar -z -cf output/p1.tar.gz  docs/  .git/  git-log *.h *.c mesh/  Makefile README.html .gitignore

