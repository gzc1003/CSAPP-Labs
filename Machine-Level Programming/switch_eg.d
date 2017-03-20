
switch_eg：     文件格式 elf64-x86-64


Disassembly of section .init:

0000000000400370 <_init>:
  400370:	48 83 ec 08          	sub    $0x8,%rsp
  400374:	48 8b 05 65 05 20 00 	mov    0x200565(%rip),%rax        # 6008e0 <_DYNAMIC+0x1d0>
  40037b:	48 85 c0             	test   %rax,%rax
  40037e:	74 05                	je     400385 <_init+0x15>
  400380:	e8 2b 00 00 00       	callq  4003b0 <__gmon_start__@plt>
  400385:	48 83 c4 08          	add    $0x8,%rsp
  400389:	c3                   	retq   

Disassembly of section .plt:

0000000000400390 <__libc_start_main@plt-0x10>:
  400390:	ff 35 5a 05 20 00    	pushq  0x20055a(%rip)        # 6008f0 <_GLOBAL_OFFSET_TABLE_+0x8>
  400396:	ff 25 5c 05 20 00    	jmpq   *0x20055c(%rip)        # 6008f8 <_GLOBAL_OFFSET_TABLE_+0x10>
  40039c:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004003a0 <__libc_start_main@plt>:
  4003a0:	ff 25 5a 05 20 00    	jmpq   *0x20055a(%rip)        # 600900 <_GLOBAL_OFFSET_TABLE_+0x18>
  4003a6:	68 00 00 00 00       	pushq  $0x0
  4003ab:	e9 e0 ff ff ff       	jmpq   400390 <_init+0x20>

00000000004003b0 <__gmon_start__@plt>:
  4003b0:	ff 25 52 05 20 00    	jmpq   *0x200552(%rip)        # 600908 <_GLOBAL_OFFSET_TABLE_+0x20>
  4003b6:	68 01 00 00 00       	pushq  $0x1
  4003bb:	e9 d0 ff ff ff       	jmpq   400390 <_init+0x20>

Disassembly of section .text:

00000000004003c0 <_start>:
  4003c0:	31 ed                	xor    %ebp,%ebp
  4003c2:	49 89 d1             	mov    %rdx,%r9
  4003c5:	5e                   	pop    %rsi
  4003c6:	48 89 e2             	mov    %rsp,%rdx
  4003c9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4003cd:	50                   	push   %rax
  4003ce:	54                   	push   %rsp
  4003cf:	49 c7 c0 70 05 40 00 	mov    $0x400570,%r8
  4003d6:	48 c7 c1 00 05 40 00 	mov    $0x400500,%rcx
  4003dd:	48 c7 c7 e8 04 40 00 	mov    $0x4004e8,%rdi
  4003e4:	e8 b7 ff ff ff       	callq  4003a0 <__libc_start_main@plt>
  4003e9:	f4                   	hlt    
  4003ea:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004003f0 <deregister_tm_clones>:
  4003f0:	b8 27 09 60 00       	mov    $0x600927,%eax
  4003f5:	55                   	push   %rbp
  4003f6:	48 2d 20 09 60 00    	sub    $0x600920,%rax
  4003fc:	48 83 f8 0e          	cmp    $0xe,%rax
  400400:	48 89 e5             	mov    %rsp,%rbp
  400403:	76 1b                	jbe    400420 <deregister_tm_clones+0x30>
  400405:	b8 00 00 00 00       	mov    $0x0,%eax
  40040a:	48 85 c0             	test   %rax,%rax
  40040d:	74 11                	je     400420 <deregister_tm_clones+0x30>
  40040f:	5d                   	pop    %rbp
  400410:	bf 20 09 60 00       	mov    $0x600920,%edi
  400415:	ff e0                	jmpq   *%rax
  400417:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  40041e:	00 00 
  400420:	5d                   	pop    %rbp
  400421:	c3                   	retq   
  400422:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 nopw %cs:0x0(%rax,%rax,1)
  400429:	1f 84 00 00 00 00 00 

0000000000400430 <register_tm_clones>:
  400430:	be 20 09 60 00       	mov    $0x600920,%esi
  400435:	55                   	push   %rbp
  400436:	48 81 ee 20 09 60 00 	sub    $0x600920,%rsi
  40043d:	48 c1 fe 03          	sar    $0x3,%rsi
  400441:	48 89 e5             	mov    %rsp,%rbp
  400444:	48 89 f0             	mov    %rsi,%rax
  400447:	48 c1 e8 3f          	shr    $0x3f,%rax
  40044b:	48 01 c6             	add    %rax,%rsi
  40044e:	48 d1 fe             	sar    %rsi
  400451:	74 15                	je     400468 <register_tm_clones+0x38>
  400453:	b8 00 00 00 00       	mov    $0x0,%eax
  400458:	48 85 c0             	test   %rax,%rax
  40045b:	74 0b                	je     400468 <register_tm_clones+0x38>
  40045d:	5d                   	pop    %rbp
  40045e:	bf 20 09 60 00       	mov    $0x600920,%edi
  400463:	ff e0                	jmpq   *%rax
  400465:	0f 1f 00             	nopl   (%rax)
  400468:	5d                   	pop    %rbp
  400469:	c3                   	retq   
  40046a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400470 <__do_global_dtors_aux>:
  400470:	80 3d a9 04 20 00 00 	cmpb   $0x0,0x2004a9(%rip)        # 600920 <__TMC_END__>
  400477:	75 11                	jne    40048a <__do_global_dtors_aux+0x1a>
  400479:	55                   	push   %rbp
  40047a:	48 89 e5             	mov    %rsp,%rbp
  40047d:	e8 6e ff ff ff       	callq  4003f0 <deregister_tm_clones>
  400482:	5d                   	pop    %rbp
  400483:	c6 05 96 04 20 00 01 	movb   $0x1,0x200496(%rip)        # 600920 <__TMC_END__>
  40048a:	f3 c3                	repz retq 
  40048c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400490 <frame_dummy>:
  400490:	bf 08 07 60 00       	mov    $0x600708,%edi
  400495:	48 83 3f 00          	cmpq   $0x0,(%rdi)
  400499:	75 05                	jne    4004a0 <frame_dummy+0x10>
  40049b:	eb 93                	jmp    400430 <register_tm_clones>
  40049d:	0f 1f 00             	nopl   (%rax)
  4004a0:	b8 00 00 00 00       	mov    $0x0,%eax
  4004a5:	48 85 c0             	test   %rax,%rax
  4004a8:	74 f1                	je     40049b <frame_dummy+0xb>
  4004aa:	55                   	push   %rbp
  4004ab:	48 89 e5             	mov    %rsp,%rbp
  4004ae:	ff d0                	callq  *%rax
  4004b0:	5d                   	pop    %rbp
  4004b1:	e9 7a ff ff ff       	jmpq   400430 <register_tm_clones>

00000000004004b6 <switch_eg>:
  4004b6:	83 ff 04             	cmp    $0x4,%edi
  4004b9:	77 21                	ja     4004dc <switch_eg+0x26>
  4004bb:	89 ff                	mov    %edi,%edi
  4004bd:	ff 24 fd 88 05 40 00 	jmpq   *0x400588(,%rdi,8)
  4004c4:	b8 01 00 00 00       	mov    $0x1,%eax
  4004c9:	c3                   	retq   
  4004ca:	b8 03 00 00 00       	mov    $0x3,%eax
  4004cf:	c3                   	retq   
  4004d0:	b8 0a 00 00 00       	mov    $0xa,%eax
  4004d5:	c3                   	retq   
  4004d6:	b8 06 00 00 00       	mov    $0x6,%eax
  4004db:	c3                   	retq   
  4004dc:	b8 00 00 00 00       	mov    $0x0,%eax
  4004e1:	c3                   	retq   
  4004e2:	b8 02 00 00 00       	mov    $0x2,%eax
  4004e7:	c3                   	retq   

00000000004004e8 <main>:
  4004e8:	bf 03 00 00 00       	mov    $0x3,%edi
  4004ed:	e8 c4 ff ff ff       	callq  4004b6 <switch_eg>
  4004f2:	f3 c3                	repz retq 
  4004f4:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4004fb:	00 00 00 
  4004fe:	66 90                	xchg   %ax,%ax

0000000000400500 <__libc_csu_init>:
  400500:	41 57                	push   %r15
  400502:	41 89 ff             	mov    %edi,%r15d
  400505:	41 56                	push   %r14
  400507:	49 89 f6             	mov    %rsi,%r14
  40050a:	41 55                	push   %r13
  40050c:	49 89 d5             	mov    %rdx,%r13
  40050f:	41 54                	push   %r12
  400511:	4c 8d 25 e0 01 20 00 	lea    0x2001e0(%rip),%r12        # 6006f8 <__frame_dummy_init_array_entry>
  400518:	55                   	push   %rbp
  400519:	48 8d 2d e0 01 20 00 	lea    0x2001e0(%rip),%rbp        # 600700 <__init_array_end>
  400520:	53                   	push   %rbx
  400521:	4c 29 e5             	sub    %r12,%rbp
  400524:	31 db                	xor    %ebx,%ebx
  400526:	48 c1 fd 03          	sar    $0x3,%rbp
  40052a:	48 83 ec 08          	sub    $0x8,%rsp
  40052e:	e8 3d fe ff ff       	callq  400370 <_init>
  400533:	48 85 ed             	test   %rbp,%rbp
  400536:	74 1e                	je     400556 <__libc_csu_init+0x56>
  400538:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40053f:	00 
  400540:	4c 89 ea             	mov    %r13,%rdx
  400543:	4c 89 f6             	mov    %r14,%rsi
  400546:	44 89 ff             	mov    %r15d,%edi
  400549:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40054d:	48 83 c3 01          	add    $0x1,%rbx
  400551:	48 39 eb             	cmp    %rbp,%rbx
  400554:	75 ea                	jne    400540 <__libc_csu_init+0x40>
  400556:	48 83 c4 08          	add    $0x8,%rsp
  40055a:	5b                   	pop    %rbx
  40055b:	5d                   	pop    %rbp
  40055c:	41 5c                	pop    %r12
  40055e:	41 5d                	pop    %r13
  400560:	41 5e                	pop    %r14
  400562:	41 5f                	pop    %r15
  400564:	c3                   	retq   
  400565:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
  40056c:	00 00 00 00 

0000000000400570 <__libc_csu_fini>:
  400570:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400574 <_fini>:
  400574:	48 83 ec 08          	sub    $0x8,%rsp
  400578:	48 83 c4 08          	add    $0x8,%rsp
  40057c:	c3                   	retq   
