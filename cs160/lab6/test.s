 # Start
 .data
 printstr: .asciz "%d\n"
 .text
 .globl Main_main
classA_classA:
  # Method Prologue
  push %ebp
  mov %esp, %ebp
  sub $0, %esp
  # Variable
  mov 12(%ebp), %eax
  push %eax
  # Assignment
pop %eax
mov 8(%ebp), %ebx
mov %eax, 0(%ebx)
  # Method epilogue
  add $0, %esp
  pop %ebp
  ret
classB_classB:
  # Method Prologue
  push %ebp
  mov %esp, %ebp
  sub $0, %esp
  # Variable
  mov 12(%ebp), %eax
  push %eax
  # Assignment
pop %eax
mov 8(%ebp), %ebx
mov %eax, 0(%ebx)
  # Variable
  mov 16(%ebp), %eax
  push %eax
  # Assignment
pop %eax
mov 8(%ebp), %ebx
mov %eax, 4(%ebx)
  # Method epilogue
  add $0, %esp
  pop %ebp
  ret
Main_main:
  # Method Prologue
  push %ebp
  mov %esp, %ebp
  sub $4, %esp
  push $8
  call malloc
  add $4, %esp
  push %eax
  #Pre-call sequence
  # BooleanLiteral
  push $1
  # IntegerLiteral
  push $12
  mov 8(%esp), %eax
  push %eax
  call classB_classB
  #Post-Return Sequence
  add $12, %esp
  # Assignment
  pop %eax
  mov %eax, -4(%ebp)
  # MemberAcces
mov -4(%ebp), %ecx
  mov 0(%ecx), %eax
  push %eax
  # Print
  push $printstr
  call printf
  add $8, %esp
  # MemberAcces
mov -4(%ebp), %ecx
  mov 4(%ecx), %eax
  push %eax
  # Print
  push $printstr
  call printf
  add $8, %esp
  # Method epilogue
  add $4, %esp
  pop %ebp
  ret
