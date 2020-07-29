awk 'BEGIN{print "Serial.println(\"\\"}{gsub(/\\/,"\\\\");gsub("\"","\\\"");print $0 "\\n\\"}END{print "\");"}' *.ino > printme.h
