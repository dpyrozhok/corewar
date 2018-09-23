.name "zork"
.comment "I'M ALIIIIVE"


den:	sti r1, %16, %1
		and 0, %0, r1
live:	live %:live
		zjmp %:live
