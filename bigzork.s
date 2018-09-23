.name "Nastya lubit Dinisa nazivat pirajok"
.comment "ya v shoke"

code:		live %42
			sti r1, %-5, %1
			zjmp %:live2	
r1:
			ldi %5, %:code, r14
			ldi %9, %:code, r13
			sti  r14, %100, %103
			sti	 r13, %100, %100
			zjmp %:code
live2:		ldi  %0, %:code, r15
			sti  r15, %100, %103
			sti r1, %94, %103
			zjmp %:r1
