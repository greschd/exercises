
comp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <fast>:
   0:	41 57                	push   %r15
   2:	41 56                	push   %r14
   4:	41 55                	push   %r13
   6:	41 54                	push   %r12
   8:	55                   	push   %rbp
   9:	53                   	push   %rbx
   a:	48 81 ec c8 00 00 00 	sub    $0xc8,%rsp
  11:	8b 47 08             	mov    0x8(%rdi),%eax
  14:	48 8b 17             	mov    (%rdi),%rdx
  17:	83 f8 01             	cmp    $0x1,%eax
  1a:	89 c1                	mov    %eax,%ecx
  1c:	89 84 24 ac 00 00 00 	mov    %eax,0xac(%rsp)
  23:	0f 8e 87 04 00 00    	jle    4b0 <fast+0x4b0>
  29:	c7 84 24 a8 00 00 00 	movl   $0x1,0xa8(%rsp)
  30:	01 00 00 00 
  34:	8d 04 40             	lea    (%rax,%rax,2),%eax
  37:	8d 3c 8d 00 00 00 00 	lea    0x0(,%rcx,4),%edi
  3e:	01 c0                	add    %eax,%eax
  40:	48 98                	cltq   
  42:	48 63 ff             	movslq %edi,%rdi
  45:	48 89 c6             	mov    %rax,%rsi
  48:	48 89 84 24 b0 00 00 	mov    %rax,0xb0(%rsp)
  4f:	00 
  50:	48 63 c1             	movslq %ecx,%rax
  53:	48 c1 e6 03          	shl    $0x3,%rsi
  57:	49 89 c7             	mov    %rax,%r15
  5a:	48 89 fb             	mov    %rdi,%rbx
  5d:	48 89 b4 24 b8 00 00 	mov    %rsi,0xb8(%rsp)
  64:	00 
  65:	8d 71 ff             	lea    -0x1(%rcx),%esi
  68:	49 f7 df             	neg    %r15
  6b:	48 8d 0c 06          	lea    (%rsi,%rax,1),%rcx
  6f:	48 c1 e7 03          	shl    $0x3,%rdi
  73:	48 29 c3             	sub    %rax,%rbx
  76:	48 8d 54 ca 08       	lea    0x8(%rdx,%rcx,8),%rdx
  7b:	49 c1 e7 03          	shl    $0x3,%r15
  7f:	48 89 5c 24 78       	mov    %rbx,0x78(%rsp)
  84:	48 89 54 24 70       	mov    %rdx,0x70(%rsp)
  89:	4a 8d 0c 3f          	lea    (%rdi,%r15,1),%rcx
  8d:	48 89 f2             	mov    %rsi,%rdx
  90:	48 f7 da             	neg    %rdx
  93:	48 c1 e6 03          	shl    $0x3,%rsi
  97:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  9e:	00 
  9f:	48 c1 e2 03          	shl    $0x3,%rdx
  a3:	48 29 f1             	sub    %rsi,%rcx
  a6:	48 8d 44 c2 f8       	lea    -0x8(%rdx,%rax,8),%rax
  ab:	48 89 84 24 90 00 00 	mov    %rax,0x90(%rsp)
  b2:	00 
  b3:	48 8d 41 f8          	lea    -0x8(%rcx),%rax
  b7:	48 8d 72 f8          	lea    -0x8(%rdx),%rsi
  bb:	48 89 84 24 88 00 00 	mov    %rax,0x88(%rsp)
  c2:	00 
  c3:	48 8d 44 17 f8       	lea    -0x8(%rdi,%rdx,1),%rax
  c8:	48 89 b4 24 98 00 00 	mov    %rsi,0x98(%rsp)
  cf:	00 
  d0:	48 89 84 24 a0 00 00 	mov    %rax,0xa0(%rsp)
  d7:	00 
  d8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  df:	00 
  e0:	4c 8b 74 24 78       	mov    0x78(%rsp),%r14
  e5:	48 8b 44 24 70       	mov    0x70(%rsp),%rax
  ea:	4c 8b ac 24 a0 00 00 	mov    0xa0(%rsp),%r13
  f1:	00 
  f2:	48 8b 8c 24 88 00 00 	mov    0x88(%rsp),%rcx
  f9:	00 
  fa:	48 8b b4 24 90 00 00 	mov    0x90(%rsp),%rsi
 101:	00 
 102:	48 8b 94 24 98 00 00 	mov    0x98(%rsp),%rdx
 109:	00 
 10a:	4c 2b b4 24 80 00 00 	sub    0x80(%rsp),%r14
 111:	00 
 112:	49 01 c5             	add    %rax,%r13
 115:	4c 8d 24 01          	lea    (%rcx,%rax,1),%r12
 119:	48 8d 2c 06          	lea    (%rsi,%rax,1),%rbp
 11d:	48 8d 1c 02          	lea    (%rdx,%rax,1),%rbx
 121:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
 128:	f2 42 0f 10 34 3b    	movsd  (%rbx,%r15,1),%xmm6
 12e:	f2 0f 10 3b          	movsd  (%rbx),%xmm7
 132:	66 0f 28 c6          	movapd %xmm6,%xmm0
 136:	f2 0f 10 6d 00       	movsd  0x0(%rbp),%xmm5
 13b:	f2 0f 11 74 24 08    	movsd  %xmm6,0x8(%rsp)
 141:	f2 0f 5c c7          	subsd  %xmm7,%xmm0
 145:	f2 41 0f 10 1c 24    	movsd  (%r12),%xmm3
 14b:	f2 0f 11 7c 24 18    	movsd  %xmm7,0x18(%rsp)
 151:	f2 41 0f 10 55 00    	movsd  0x0(%r13),%xmm2
 157:	f2 0f 11 6c 24 28    	movsd  %xmm5,0x28(%rsp)
 15d:	f2 42 0f 10 2c f3    	movsd  (%rbx,%r14,8),%xmm5
 163:	f2 0f 11 5c 24 30    	movsd  %xmm3,0x30(%rsp)
 169:	f2 0f 11 54 24 38    	movsd  %xmm2,0x38(%rsp)
 16f:	f2 0f 11 6c 24 10    	movsd  %xmm5,0x10(%rsp)
 175:	e8 00 00 00 00       	callq  17a <fast+0x17a>
 17a:	f2 0f 10 7c 24 08    	movsd  0x8(%rsp),%xmm7
 180:	f2 0f 11 44 24 40    	movsd  %xmm0,0x40(%rsp)
 186:	f2 0f 58 7c 24 18    	addsd  0x18(%rsp),%xmm7
 18c:	66 0f 28 c7          	movapd %xmm7,%xmm0
 190:	e8 00 00 00 00       	callq  195 <fast+0x195>
 195:	f2 0f 10 35 00 00 00 	movsd  0x0(%rip),%xmm6        # 19d <fast+0x19d>
 19c:	00 
 19d:	f2 0f 11 44 24 68    	movsd  %xmm0,0x68(%rsp)
 1a3:	f2 0f 10 44 24 10    	movsd  0x10(%rsp),%xmm0
 1a9:	f2 0f 59 74 24 40    	mulsd  0x40(%rsp),%xmm6
 1af:	f2 0f 58 44 24 30    	addsd  0x30(%rsp),%xmm0
 1b5:	f2 0f 11 74 24 48    	movsd  %xmm6,0x48(%rsp)
 1bb:	e8 00 00 00 00       	callq  1c0 <fast+0x1c0>
 1c0:	f2 0f 11 44 24 50    	movsd  %xmm0,0x50(%rsp)
 1c6:	f2 0f 10 44 24 10    	movsd  0x10(%rsp),%xmm0
 1cc:	f2 0f 5c 44 24 30    	subsd  0x30(%rsp),%xmm0
 1d2:	e8 00 00 00 00       	callq  1d7 <fast+0x1d7>
 1d7:	f2 0f 10 0d 00 00 00 	movsd  0x0(%rip),%xmm1        # 1df <fast+0x1df>
 1de:	00 
 1df:	f2 0f 10 2d 00 00 00 	movsd  0x0(%rip),%xmm5        # 1e7 <fast+0x1e7>
 1e6:	00 
 1e7:	f2 0f 59 4c 24 08    	mulsd  0x8(%rsp),%xmm1
 1ed:	f2 0f 58 6c 24 18    	addsd  0x18(%rsp),%xmm5
 1f3:	f2 0f 10 35 00 00 00 	movsd  0x0(%rip),%xmm6        # 1fb <fast+0x1fb>
 1fa:	00 
 1fb:	f2 0f 59 f0          	mulsd  %xmm0,%xmm6
 1ff:	f2 0f 11 6c 24 20    	movsd  %xmm5,0x20(%rsp)
 205:	f2 0f 58 cd          	addsd  %xmm5,%xmm1
 209:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 20d:	f2 0f 11 74 24 58    	movsd  %xmm6,0x58(%rsp)
 213:	f2 0f 10 35 00 00 00 	movsd  0x0(%rip),%xmm6        # 21b <fast+0x21b>
 21a:	00 
 21b:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 21f:	f2 0f 58 74 24 30    	addsd  0x30(%rsp),%xmm6
 225:	f2 0f 11 74 24 18    	movsd  %xmm6,0x18(%rsp)
 22b:	0f 8a 91 02 00 00    	jp     4c2 <fast+0x4c2>
 231:	e8 00 00 00 00       	callq  236 <fast+0x236>
 236:	f2 0f 10 0d 00 00 00 	movsd  0x0(%rip),%xmm1        # 23e <fast+0x23e>
 23d:	00 
 23e:	f2 0f 11 44 24 30    	movsd  %xmm0,0x30(%rsp)
 244:	f2 0f 59 4c 24 10    	mulsd  0x10(%rsp),%xmm1
 24a:	f2 0f 58 4c 24 18    	addsd  0x18(%rsp),%xmm1
 250:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 254:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 258:	0f 8a 72 02 00 00    	jp     4d0 <fast+0x4d0>
 25e:	e8 00 00 00 00       	callq  263 <fast+0x263>
 263:	f2 0f 10 4c 24 20    	movsd  0x20(%rsp),%xmm1
 269:	f2 0f 11 44 24 60    	movsd  %xmm0,0x60(%rsp)
 26f:	f2 0f 5c 4c 24 28    	subsd  0x28(%rsp),%xmm1
 275:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 279:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 27d:	0f 8a 5b 02 00 00    	jp     4de <fast+0x4de>
 283:	e8 00 00 00 00       	callq  288 <fast+0x288>
 288:	f2 0f 10 15 00 00 00 	movsd  0x0(%rip),%xmm2        # 290 <fast+0x290>
 28f:	00 
 290:	f2 0f 10 7c 24 20    	movsd  0x20(%rsp),%xmm7
 296:	f2 0f 59 54 24 68    	mulsd  0x68(%rsp),%xmm2
 29c:	f2 0f 10 4c 24 40    	movsd  0x40(%rsp),%xmm1
 2a2:	f2 0f 59 cf          	mulsd  %xmm7,%xmm1
 2a6:	f2 0f 59 54 24 28    	mulsd  0x28(%rsp),%xmm2
 2ac:	f2 0f 59 54 24 30    	mulsd  0x30(%rsp),%xmm2
 2b2:	f2 0f 5c d1          	subsd  %xmm1,%xmm2
 2b6:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 2bc:	f2 0f 59 4c 24 48    	mulsd  0x48(%rsp),%xmm1
 2c2:	f2 0f 59 c8          	mulsd  %xmm0,%xmm1
 2c6:	f2 0f 51 c7          	sqrtsd %xmm7,%xmm0
 2ca:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 2ce:	f2 0f 5c d1          	subsd  %xmm1,%xmm2
 2d2:	0f 8a 14 02 00 00    	jp     4ec <fast+0x4ec>
 2d8:	f2 0f 11 54 24 68    	movsd  %xmm2,0x68(%rsp)
 2de:	e8 00 00 00 00       	callq  2e3 <fast+0x2e3>
 2e3:	f2 0f 10 7c 24 40    	movsd  0x40(%rsp),%xmm7
 2e9:	f2 0f 10 5c 24 28    	movsd  0x28(%rsp),%xmm3
 2ef:	f2 0f 10 4c 24 48    	movsd  0x48(%rsp),%xmm1
 2f5:	f2 0f 59 df          	mulsd  %xmm7,%xmm3
 2f9:	f2 0f 10 54 24 68    	movsd  0x68(%rsp),%xmm2
 2ff:	f2 0f 59 4c 24 20    	mulsd  0x20(%rsp),%xmm1
 305:	f2 0f 59 d8          	mulsd  %xmm0,%xmm3
 309:	f2 0f 10 44 24 08    	movsd  0x8(%rsp),%xmm0
 30f:	f2 0f 59 c7          	mulsd  %xmm7,%xmm0
 313:	f2 0f 5c d9          	subsd  %xmm1,%xmm3
 317:	f2 0f 10 4c 24 18    	movsd  0x18(%rsp),%xmm1
 31d:	f2 0f 59 44 24 30    	mulsd  0x30(%rsp),%xmm0
 323:	f2 0f 5c 4c 24 38    	subsd  0x38(%rsp),%xmm1
 329:	f2 0f 5c d8          	subsd  %xmm0,%xmm3
 32d:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 331:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 335:	0f 8a cb 01 00 00    	jp     506 <fast+0x506>
 33b:	f2 0f 11 5c 24 20    	movsd  %xmm3,0x20(%rsp)
 341:	f2 0f 11 54 24 08    	movsd  %xmm2,0x8(%rsp)
 347:	e8 00 00 00 00       	callq  34c <fast+0x34c>
 34c:	f2 0f 10 64 24 50    	movsd  0x50(%rsp),%xmm4
 352:	f2 0f 10 0d 00 00 00 	movsd  0x0(%rip),%xmm1        # 35a <fast+0x35a>
 359:	00 
 35a:	f2 0f 10 6c 24 18    	movsd  0x18(%rsp),%xmm5
 360:	f2 0f 59 cc          	mulsd  %xmm4,%xmm1
 364:	f2 0f 10 54 24 08    	movsd  0x8(%rsp),%xmm2
 36a:	f2 0f 59 e5          	mulsd  %xmm5,%xmm4
 36e:	f2 0f 10 5c 24 20    	movsd  0x20(%rsp),%xmm3
 374:	f2 0f 59 4c 24 38    	mulsd  0x38(%rsp),%xmm1
 37a:	f2 0f 59 4c 24 60    	mulsd  0x60(%rsp),%xmm1
 380:	f2 0f 5c cc          	subsd  %xmm4,%xmm1
 384:	f2 0f 10 64 24 10    	movsd  0x10(%rsp),%xmm4
 38a:	f2 0f 59 64 24 58    	mulsd  0x58(%rsp),%xmm4
 390:	f2 0f 59 e0          	mulsd  %xmm0,%xmm4
 394:	f2 0f 51 c5          	sqrtsd %xmm5,%xmm0
 398:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 39c:	f2 0f 5c cc          	subsd  %xmm4,%xmm1
 3a0:	0f 8a 86 01 00 00    	jp     52c <fast+0x52c>
 3a6:	f2 0f 11 4c 24 28    	movsd  %xmm1,0x28(%rsp)
 3ac:	48 83 c5 08          	add    $0x8,%rbp
 3b0:	49 83 c4 08          	add    $0x8,%r12
 3b4:	f2 0f 11 5c 24 20    	movsd  %xmm3,0x20(%rsp)
 3ba:	49 83 c5 08          	add    $0x8,%r13
 3be:	f2 0f 11 54 24 08    	movsd  %xmm2,0x8(%rsp)
 3c4:	e8 00 00 00 00       	callq  3c9 <fast+0x3c9>
 3c9:	f2 0f 10 7c 24 50    	movsd  0x50(%rsp),%xmm7
 3cf:	f2 0f 10 64 24 38    	movsd  0x38(%rsp),%xmm4
 3d5:	f2 0f 10 6c 24 58    	movsd  0x58(%rsp),%xmm5
 3db:	f2 0f 59 e7          	mulsd  %xmm7,%xmm4
 3df:	f2 0f 10 5c 24 20    	movsd  0x20(%rsp),%xmm3
 3e5:	f2 0f 59 6c 24 18    	mulsd  0x18(%rsp),%xmm5
 3eb:	f2 0f 10 54 24 08    	movsd  0x8(%rsp),%xmm2
 3f1:	f2 0f 10 4c 24 28    	movsd  0x28(%rsp),%xmm1
 3f7:	f2 0f 59 e0          	mulsd  %xmm0,%xmm4
 3fb:	f2 0f 10 44 24 10    	movsd  0x10(%rsp),%xmm0
 401:	f2 0f 59 c7          	mulsd  %xmm7,%xmm0
 405:	f2 0f 5c e5          	subsd  %xmm5,%xmm4
 409:	f2 0f 59 44 24 60    	mulsd  0x60(%rsp),%xmm0
 40f:	f2 0f 5c e0          	subsd  %xmm0,%xmm4
 413:	66 0f 28 c3          	movapd %xmm3,%xmm0
 417:	f2 0f 58 c2          	addsd  %xmm2,%xmm0
 41b:	f2 0f 58 c0          	addsd  %xmm0,%xmm0
 41f:	f2 42 0f 11 04 3b    	movsd  %xmm0,(%rbx,%r15,1)
 425:	66 0f 28 c4          	movapd %xmm4,%xmm0
 429:	f2 0f 58 1b          	addsd  (%rbx),%xmm3
 42d:	f2 0f 58 c1          	addsd  %xmm1,%xmm0
 431:	f2 0f 11 1b          	movsd  %xmm3,(%rbx)
 435:	f2 0f 58 55 f8       	addsd  -0x8(%rbp),%xmm2
 43a:	f2 0f 58 c0          	addsd  %xmm0,%xmm0
 43e:	f2 0f 11 55 f8       	movsd  %xmm2,-0x8(%rbp)
 443:	f2 42 0f 11 04 f3    	movsd  %xmm0,(%rbx,%r14,8)
 449:	48 83 c3 08          	add    $0x8,%rbx
 44d:	f2 41 0f 58 64 24 f8 	addsd  -0x8(%r12),%xmm4
 454:	f2 41 0f 11 64 24 f8 	movsd  %xmm4,-0x8(%r12)
 45b:	f2 41 0f 58 4d f8    	addsd  -0x8(%r13),%xmm1
 461:	f2 41 0f 11 4d f8    	movsd  %xmm1,-0x8(%r13)
 467:	48 39 5c 24 70       	cmp    %rbx,0x70(%rsp)
 46c:	0f 85 b6 fc ff ff    	jne    128 <fast+0x128>
 472:	48 8b 84 24 b0 00 00 	mov    0xb0(%rsp),%rax
 479:	00 
 47a:	83 84 24 a8 00 00 00 	addl   $0x6,0xa8(%rsp)
 481:	06 
 482:	48 01 44 24 78       	add    %rax,0x78(%rsp)
 487:	48 01 84 24 80 00 00 	add    %rax,0x80(%rsp)
 48e:	00 
 48f:	48 8b 84 24 b8 00 00 	mov    0xb8(%rsp),%rax
 496:	00 
 497:	48 01 44 24 70       	add    %rax,0x70(%rsp)
 49c:	8b 84 24 a8 00 00 00 	mov    0xa8(%rsp),%eax
 4a3:	39 84 24 ac 00 00 00 	cmp    %eax,0xac(%rsp)
 4aa:	0f 8f 30 fc ff ff    	jg     e0 <fast+0xe0>
 4b0:	48 81 c4 c8 00 00 00 	add    $0xc8,%rsp
 4b7:	5b                   	pop    %rbx
 4b8:	5d                   	pop    %rbp
 4b9:	41 5c                	pop    %r12
 4bb:	41 5d                	pop    %r13
 4bd:	41 5e                	pop    %r14
 4bf:	41 5f                	pop    %r15
 4c1:	c3                   	retq   
 4c2:	66 0f 28 c1          	movapd %xmm1,%xmm0
 4c6:	e8 00 00 00 00       	callq  4cb <fast+0x4cb>
 4cb:	e9 61 fd ff ff       	jmpq   231 <fast+0x231>
 4d0:	66 0f 28 c1          	movapd %xmm1,%xmm0
 4d4:	e8 00 00 00 00       	callq  4d9 <fast+0x4d9>
 4d9:	e9 80 fd ff ff       	jmpq   25e <fast+0x25e>
 4de:	66 0f 28 c1          	movapd %xmm1,%xmm0
 4e2:	e8 00 00 00 00       	callq  4e7 <fast+0x4e7>
 4e7:	e9 97 fd ff ff       	jmpq   283 <fast+0x283>
 4ec:	66 0f 28 c7          	movapd %xmm7,%xmm0
 4f0:	f2 0f 11 54 24 68    	movsd  %xmm2,0x68(%rsp)
 4f6:	e8 00 00 00 00       	callq  4fb <fast+0x4fb>
 4fb:	f2 0f 10 54 24 68    	movsd  0x68(%rsp),%xmm2
 501:	e9 d2 fd ff ff       	jmpq   2d8 <fast+0x2d8>
 506:	66 0f 28 c1          	movapd %xmm1,%xmm0
 50a:	f2 0f 11 5c 24 20    	movsd  %xmm3,0x20(%rsp)
 510:	f2 0f 11 54 24 08    	movsd  %xmm2,0x8(%rsp)
 516:	e8 00 00 00 00       	callq  51b <fast+0x51b>
 51b:	f2 0f 10 5c 24 20    	movsd  0x20(%rsp),%xmm3
 521:	f2 0f 10 54 24 08    	movsd  0x8(%rsp),%xmm2
 527:	e9 0f fe ff ff       	jmpq   33b <fast+0x33b>
 52c:	66 0f 28 c5          	movapd %xmm5,%xmm0
 530:	f2 0f 11 4c 24 28    	movsd  %xmm1,0x28(%rsp)
 536:	e8 00 00 00 00       	callq  53b <fast+0x53b>
 53b:	f2 0f 10 4c 24 28    	movsd  0x28(%rsp),%xmm1
 541:	f2 0f 10 5c 24 20    	movsd  0x20(%rsp),%xmm3
 547:	f2 0f 10 54 24 08    	movsd  0x8(%rsp),%xmm2
 54d:	e9 54 fe ff ff       	jmpq   3a6 <fast+0x3a6>
 552:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
 559:	1f 84 00 00 00 00 00 

0000000000000560 <f>:
 560:	41 54                	push   %r12
 562:	49 89 f4             	mov    %rsi,%r12
 565:	55                   	push   %rbp
 566:	89 d5                	mov    %edx,%ebp
 568:	53                   	push   %rbx
 569:	d1 fd                	sar    %ebp
 56b:	48 89 fb             	mov    %rdi,%rbx
 56e:	48 83 ec 50          	sub    $0x50,%rsp
 572:	f2 0f 11 04 24       	movsd  %xmm0,(%rsp)
 577:	f2 0f 2a c2          	cvtsi2sd %edx,%xmm0
 57b:	f2 0f 11 4c 24 08    	movsd  %xmm1,0x8(%rsp)
 581:	f2 0f 11 54 24 20    	movsd  %xmm2,0x20(%rsp)
 587:	f2 0f 59 05 00 00 00 	mulsd  0x0(%rip),%xmm0        # 58f <f+0x2f>
 58e:	00 
 58f:	e8 00 00 00 00       	callq  594 <f+0x34>
 594:	f3 0f 2a cd          	cvtsi2ss %ebp,%xmm1
 598:	0f 14 c9             	unpcklps %xmm1,%xmm1
 59b:	0f 5a c9             	cvtps2pd %xmm1,%xmm1
 59e:	66 0f 2e c1          	ucomisd %xmm1,%xmm0
 5a2:	0f 8b 18 02 00 00    	jnp    7c0 <f+0x260>
 5a8:	f2 0f 10 44 24 08    	movsd  0x8(%rsp),%xmm0
 5ae:	48 8d 74 24 40       	lea    0x40(%rsp),%rsi
 5b3:	48 8d 7c 24 48       	lea    0x48(%rsp),%rdi
 5b8:	e8 00 00 00 00       	callq  5bd <f+0x5d>
 5bd:	48 8b 6c 24 48       	mov    0x48(%rsp),%rbp
 5c2:	48 8d 74 24 40       	lea    0x40(%rsp),%rsi
 5c7:	f2 0f 10 74 24 40    	movsd  0x40(%rsp),%xmm6
 5cd:	48 8d 7c 24 48       	lea    0x48(%rsp),%rdi
 5d2:	f2 0f 10 04 24       	movsd  (%rsp),%xmm0
 5d7:	f2 0f 11 74 24 10    	movsd  %xmm6,0x10(%rsp)
 5dd:	e8 00 00 00 00       	callq  5e2 <f+0x82>
 5e2:	f2 0f 10 74 24 10    	movsd  0x10(%rsp),%xmm6
 5e8:	66 48 0f 6e c5       	movq   %rbp,%xmm0
 5ed:	f2 0f 59 44 24 40    	mulsd  0x40(%rsp),%xmm0
 5f3:	f2 0f 59 74 24 48    	mulsd  0x48(%rsp),%xmm6
 5f9:	f2 0f 5c f0          	subsd  %xmm0,%xmm6
 5fd:	f2 0f 11 74 24 10    	movsd  %xmm6,0x10(%rsp)
 603:	f2 0f 10 04 24       	movsd  (%rsp),%xmm0
 608:	f2 0f 58 44 24 08    	addsd  0x8(%rsp),%xmm0
 60e:	e8 00 00 00 00       	callq  613 <f+0xb3>
 613:	66 48 0f 7e c5       	movq   %xmm0,%rbp
 618:	f2 0f 10 04 24       	movsd  (%rsp),%xmm0
 61d:	f2 0f 5c 44 24 08    	subsd  0x8(%rsp),%xmm0
 623:	e8 00 00 00 00       	callq  628 <f+0xc8>
 628:	f2 0f 10 1d 00 00 00 	movsd  0x0(%rip),%xmm3        # 630 <f+0xd0>
 62f:	00 
 630:	f2 0f 10 64 24 08    	movsd  0x8(%rsp),%xmm4
 636:	f2 0f 59 1c 24       	mulsd  (%rsp),%xmm3
 63b:	f2 0f 10 2d 00 00 00 	movsd  0x0(%rip),%xmm5        # 643 <f+0xe3>
 642:	00 
 643:	f2 0f 10 35 00 00 00 	movsd  0x0(%rip),%xmm6        # 64b <f+0xeb>
 64a:	00 
 64b:	f2 0f 59 e8          	mulsd  %xmm0,%xmm5
 64f:	f2 0f 58 f4          	addsd  %xmm4,%xmm6
 653:	66 0f 28 cb          	movapd %xmm3,%xmm1
 657:	f2 0f 11 5c 24 30    	movsd  %xmm3,0x30(%rsp)
 65d:	f2 0f 58 cc          	addsd  %xmm4,%xmm1
 661:	f2 0f 11 74 24 18    	movsd  %xmm6,0x18(%rsp)
 667:	f2 0f 11 6c 24 28    	movsd  %xmm5,0x28(%rsp)
 66d:	f2 0f 58 0d 00 00 00 	addsd  0x0(%rip),%xmm1        # 675 <f+0x115>
 674:	00 
 675:	66 0f 54 0d 00 00 00 	andpd  0x0(%rip),%xmm1        # 67d <f+0x11d>
 67c:	00 
 67d:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 681:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 685:	0f 8a c2 01 00 00    	jp     84d <f+0x2ed>
 68b:	e8 00 00 00 00       	callq  690 <f+0x130>
 690:	f2 0f 10 4c 24 20    	movsd  0x20(%rsp),%xmm1
 696:	f2 0f 11 44 24 38    	movsd  %xmm0,0x38(%rsp)
 69c:	f2 0f 5c 4c 24 08    	subsd  0x8(%rsp),%xmm1
 6a2:	f2 0f 5c 0d 00 00 00 	subsd  0x0(%rip),%xmm1        # 6aa <f+0x14a>
 6a9:	00 
 6aa:	66 0f 54 0d 00 00 00 	andpd  0x0(%rip),%xmm1        # 6b2 <f+0x152>
 6b1:	00 
 6b2:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 6b6:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 6ba:	0f 8a 7f 01 00 00    	jp     83f <f+0x2df>
 6c0:	e8 00 00 00 00       	callq  6c5 <f+0x165>
 6c5:	66 48 0f 6e cd       	movq   %rbp,%xmm1
 6ca:	f2 0f 10 54 24 10    	movsd  0x10(%rsp),%xmm2
 6d0:	f2 0f 59 0d 00 00 00 	mulsd  0x0(%rip),%xmm1        # 6d8 <f+0x178>
 6d7:	00 
 6d8:	f2 0f 59 54 24 18    	mulsd  0x18(%rsp),%xmm2
 6de:	f2 0f 10 7c 24 08    	movsd  0x8(%rsp),%xmm7
 6e4:	f2 0f 59 4c 24 20    	mulsd  0x20(%rsp),%xmm1
 6ea:	f2 0f 59 4c 24 38    	mulsd  0x38(%rsp),%xmm1
 6f0:	f2 0f 5c ca          	subsd  %xmm2,%xmm1
 6f4:	f2 0f 10 14 24       	movsd  (%rsp),%xmm2
 6f9:	f2 0f 59 54 24 28    	mulsd  0x28(%rsp),%xmm2
 6ff:	f2 0f 59 d0          	mulsd  %xmm0,%xmm2
 703:	f2 0f 5c ca          	subsd  %xmm2,%xmm1
 707:	f2 0f 11 0b          	movsd  %xmm1,(%rbx)
 70b:	f2 0f 10 0d 00 00 00 	movsd  0x0(%rip),%xmm1        # 713 <f+0x1b3>
 712:	00 
 713:	66 0f 57 f9          	xorpd  %xmm1,%xmm7
 717:	66 0f 28 cf          	movapd %xmm7,%xmm1
 71b:	f2 0f 5c 0d 00 00 00 	subsd  0x0(%rip),%xmm1        # 723 <f+0x1c3>
 722:	00 
 723:	66 0f 54 0d 00 00 00 	andpd  0x0(%rip),%xmm1        # 72b <f+0x1cb>
 72a:	00 
 72b:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 72f:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 733:	0f 8a f8 00 00 00    	jp     831 <f+0x2d1>
 739:	e8 00 00 00 00       	callq  73e <f+0x1de>
 73e:	f2 0f 10 4c 24 30    	movsd  0x30(%rsp),%xmm1
 744:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%rsp)
 74a:	f2 0f 58 4c 24 18    	addsd  0x18(%rsp),%xmm1
 750:	66 0f 54 0d 00 00 00 	andpd  0x0(%rip),%xmm1        # 758 <f+0x1f8>
 757:	00 
 758:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 75c:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 760:	0f 8a bd 00 00 00    	jp     823 <f+0x2c3>
 766:	e8 00 00 00 00       	callq  76b <f+0x20b>
 76b:	f2 0f 10 64 24 10    	movsd  0x10(%rsp),%xmm4
 771:	f2 0f 10 4c 24 20    	movsd  0x20(%rsp),%xmm1
 777:	f2 0f 10 54 24 18    	movsd  0x18(%rsp),%xmm2
 77d:	f2 0f 59 cc          	mulsd  %xmm4,%xmm1
 781:	f2 0f 59 54 24 28    	mulsd  0x28(%rsp),%xmm2
 787:	f2 0f 59 4c 24 08    	mulsd  0x8(%rsp),%xmm1
 78d:	f2 0f 5c ca          	subsd  %xmm2,%xmm1
 791:	f2 0f 10 14 24       	movsd  (%rsp),%xmm2
 796:	f2 0f 59 d4          	mulsd  %xmm4,%xmm2
 79a:	f2 0f 59 d0          	mulsd  %xmm0,%xmm2
 79e:	f2 0f 5c ca          	subsd  %xmm2,%xmm1
 7a2:	f2 41 0f 11 0c 24    	movsd  %xmm1,(%r12)
 7a8:	f2 0f 58 0b          	addsd  (%rbx),%xmm1
 7ac:	48 83 c4 50          	add    $0x50,%rsp
 7b0:	5b                   	pop    %rbx
 7b1:	66 0f 28 c1          	movapd %xmm1,%xmm0
 7b5:	5d                   	pop    %rbp
 7b6:	41 5c                	pop    %r12
 7b8:	c3                   	retq   
 7b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
 7c0:	0f 85 e2 fd ff ff    	jne    5a8 <f+0x48>
 7c6:	f2 0f 10 04 24       	movsd  (%rsp),%xmm0
 7cb:	e8 00 00 00 00       	callq  7d0 <f+0x270>
 7d0:	f2 0f 11 44 24 10    	movsd  %xmm0,0x10(%rsp)
 7d6:	f2 0f 10 44 24 08    	movsd  0x8(%rsp),%xmm0
 7dc:	e8 00 00 00 00       	callq  7e1 <f+0x281>
 7e1:	f2 0f 11 44 24 18    	movsd  %xmm0,0x18(%rsp)
 7e7:	f2 0f 10 04 24       	movsd  (%rsp),%xmm0
 7ec:	e8 00 00 00 00       	callq  7f1 <f+0x291>
 7f1:	f2 0f 11 44 24 28    	movsd  %xmm0,0x28(%rsp)
 7f7:	f2 0f 10 44 24 08    	movsd  0x8(%rsp),%xmm0
 7fd:	e8 00 00 00 00       	callq  802 <f+0x2a2>
 802:	f2 0f 10 7c 24 10    	movsd  0x10(%rsp),%xmm7
 808:	f2 0f 59 44 24 28    	mulsd  0x28(%rsp),%xmm0
 80e:	f2 0f 59 7c 24 18    	mulsd  0x18(%rsp),%xmm7
 814:	f2 0f 58 c7          	addsd  %xmm7,%xmm0
 818:	f2 0f 11 44 24 10    	movsd  %xmm0,0x10(%rsp)
 81e:	e9 e0 fd ff ff       	jmpq   603 <f+0xa3>
 823:	66 0f 28 c1          	movapd %xmm1,%xmm0
 827:	e8 00 00 00 00       	callq  82c <f+0x2cc>
 82c:	e9 35 ff ff ff       	jmpq   766 <f+0x206>
 831:	66 0f 28 c1          	movapd %xmm1,%xmm0
 835:	e8 00 00 00 00       	callq  83a <f+0x2da>
 83a:	e9 fa fe ff ff       	jmpq   739 <f+0x1d9>
 83f:	66 0f 28 c1          	movapd %xmm1,%xmm0
 843:	e8 00 00 00 00       	callq  848 <f+0x2e8>
 848:	e9 73 fe ff ff       	jmpq   6c0 <f+0x160>
 84d:	66 0f 28 c1          	movapd %xmm1,%xmm0
 851:	e8 00 00 00 00       	callq  856 <f+0x2f6>
 856:	e9 30 fe ff ff       	jmpq   68b <f+0x12b>
 85b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000000860 <superslow>:
 860:	41 57                	push   %r15
 862:	41 56                	push   %r14
 864:	41 55                	push   %r13
 866:	41 54                	push   %r12
 868:	55                   	push   %rbp
 869:	48 89 fd             	mov    %rdi,%rbp
 86c:	53                   	push   %rbx
 86d:	48 83 ec 38          	sub    $0x38,%rsp
 871:	8b 47 08             	mov    0x8(%rdi),%eax
 874:	85 c0                	test   %eax,%eax
 876:	0f 8e 4f 01 00 00    	jle    9cb <superslow+0x16b>
 87c:	45 31 e4             	xor    %r12d,%r12d
 87f:	90                   	nop
 880:	83 f8 01             	cmp    $0x1,%eax
 883:	0f 8e 42 01 00 00    	jle    9cb <superslow+0x16b>
 889:	bb 01 00 00 00       	mov    $0x1,%ebx
 88e:	66 90                	xchg   %ax,%ax
 890:	44 8d 73 ff          	lea    -0x1(%rbx),%r14d
 894:	44 89 e2             	mov    %r12d,%edx
 897:	48 89 ef             	mov    %rbp,%rdi
 89a:	44 8d 6b 01          	lea    0x1(%rbx),%r13d
 89e:	44 89 f6             	mov    %r14d,%esi
 8a1:	e8 00 00 00 00       	callq  8a6 <superslow+0x46>
 8a6:	89 de                	mov    %ebx,%esi
 8a8:	44 89 e2             	mov    %r12d,%edx
 8ab:	48 89 ef             	mov    %rbp,%rdi
 8ae:	66 49 0f 7e c7       	movq   %xmm0,%r15
 8b3:	e8 00 00 00 00       	callq  8b8 <superslow+0x58>
 8b8:	44 89 e2             	mov    %r12d,%edx
 8bb:	44 89 ee             	mov    %r13d,%esi
 8be:	48 89 ef             	mov    %rbp,%rdi
 8c1:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%rsp)
 8c7:	e8 00 00 00 00       	callq  8cc <superslow+0x6c>
 8cc:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 8d2:	89 da                	mov    %ebx,%edx
 8d4:	48 8d 74 24 28       	lea    0x28(%rsp),%rsi
 8d9:	66 0f 28 d0          	movapd %xmm0,%xmm2
 8dd:	f2 0f 11 44 24 18    	movsd  %xmm0,0x18(%rsp)
 8e3:	48 8d 7c 24 20       	lea    0x20(%rsp),%rdi
 8e8:	66 49 0f 6e c7       	movq   %r15,%xmm0
 8ed:	e8 00 00 00 00       	callq  8f2 <superslow+0x92>
 8f2:	f2 0f 10 5c 24 18    	movsd  0x18(%rsp),%xmm3
 8f8:	89 da                	mov    %ebx,%edx
 8fa:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 900:	f2 0f 11 44 24 10    	movsd  %xmm0,0x10(%rsp)
 906:	48 8d 74 24 20       	lea    0x20(%rsp),%rsi
 90b:	48 8d 7c 24 28       	lea    0x28(%rsp),%rdi
 910:	66 0f 28 d3          	movapd %xmm3,%xmm2
 914:	66 49 0f 6e c7       	movq   %r15,%xmm0
 919:	e8 00 00 00 00       	callq  91e <superslow+0xbe>
 91e:	f2 0f 10 4c 24 10    	movsd  0x10(%rsp),%xmm1
 924:	89 de                	mov    %ebx,%esi
 926:	44 89 e2             	mov    %r12d,%edx
 929:	48 89 ef             	mov    %rbp,%rdi
 92c:	f2 0f 58 c8          	addsd  %xmm0,%xmm1
 930:	f2 0f 11 4c 24 18    	movsd  %xmm1,0x18(%rsp)
 936:	e8 00 00 00 00       	callq  93b <superslow+0xdb>
 93b:	f2 0f 10 5c 24 20    	movsd  0x20(%rsp),%xmm3
 941:	44 89 e2             	mov    %r12d,%edx
 944:	44 89 ee             	mov    %r13d,%esi
 947:	48 89 ef             	mov    %rbp,%rdi
 94a:	f2 0f 58 d8          	addsd  %xmm0,%xmm3
 94e:	f2 0f 11 5c 24 10    	movsd  %xmm3,0x10(%rsp)
 954:	e8 00 00 00 00       	callq  959 <superslow+0xf9>
 959:	f2 0f 10 54 24 28    	movsd  0x28(%rsp),%xmm2
 95f:	44 89 e2             	mov    %r12d,%edx
 962:	f2 0f 10 4c 24 18    	movsd  0x18(%rsp),%xmm1
 968:	44 89 f6             	mov    %r14d,%esi
 96b:	48 89 ef             	mov    %rbp,%rdi
 96e:	f2 0f 58 d0          	addsd  %xmm0,%xmm2
 972:	66 0f 28 c1          	movapd %xmm1,%xmm0
 976:	f2 0f 11 54 24 08    	movsd  %xmm2,0x8(%rsp)
 97c:	e8 00 00 00 00       	callq  981 <superslow+0x121>
 981:	f2 0f 10 5c 24 10    	movsd  0x10(%rsp),%xmm3
 987:	89 de                	mov    %ebx,%esi
 989:	44 89 e2             	mov    %r12d,%edx
 98c:	48 89 ef             	mov    %rbp,%rdi
 98f:	83 c3 03             	add    $0x3,%ebx
 992:	66 0f 28 c3          	movapd %xmm3,%xmm0
 996:	e8 00 00 00 00       	callq  99b <superslow+0x13b>
 99b:	f2 0f 10 54 24 08    	movsd  0x8(%rsp),%xmm2
 9a1:	44 89 e2             	mov    %r12d,%edx
 9a4:	44 89 ee             	mov    %r13d,%esi
 9a7:	48 89 ef             	mov    %rbp,%rdi
 9aa:	66 0f 28 c2          	movapd %xmm2,%xmm0
 9ae:	e8 00 00 00 00       	callq  9b3 <superslow+0x153>
 9b3:	8b 45 08             	mov    0x8(%rbp),%eax
 9b6:	39 d8                	cmp    %ebx,%eax
 9b8:	0f 8f d2 fe ff ff    	jg     890 <superslow+0x30>
 9be:	41 83 c4 01          	add    $0x1,%r12d
 9c2:	44 39 e0             	cmp    %r12d,%eax
 9c5:	0f 8f b5 fe ff ff    	jg     880 <superslow+0x20>
 9cb:	48 83 c4 38          	add    $0x38,%rsp
 9cf:	5b                   	pop    %rbx
 9d0:	5d                   	pop    %rbp
 9d1:	41 5c                	pop    %r12
 9d3:	41 5d                	pop    %r13
 9d5:	41 5e                	pop    %r14
 9d7:	41 5f                	pop    %r15
 9d9:	c3                   	retq   
 9da:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000009e0 <fasterf>:
 9e0:	41 56                	push   %r14
 9e2:	55                   	push   %rbp
 9e3:	48 89 f5             	mov    %rsi,%rbp
 9e6:	53                   	push   %rbx
 9e7:	48 89 fb             	mov    %rdi,%rbx
 9ea:	48 83 ec 30          	sub    $0x30,%rsp
 9ee:	83 e2 01             	and    $0x1,%edx
 9f1:	f2 0f 11 04 24       	movsd  %xmm0,(%rsp)
 9f6:	f2 0f 11 54 24 10    	movsd  %xmm2,0x10(%rsp)
 9fc:	0f 84 4e 01 00 00    	je     b50 <fasterf+0x170>
 a02:	f2 0f 5c c1          	subsd  %xmm1,%xmm0
 a06:	f2 0f 11 4c 24 08    	movsd  %xmm1,0x8(%rsp)
 a0c:	e8 00 00 00 00       	callq  a11 <fasterf+0x31>
 a11:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 a17:	f2 0f 11 44 24 18    	movsd  %xmm0,0x18(%rsp)
 a1d:	f2 0f 10 04 24       	movsd  (%rsp),%xmm0
 a22:	f2 0f 58 c1          	addsd  %xmm1,%xmm0
 a26:	e8 00 00 00 00       	callq  a2b <fasterf+0x4b>
 a2b:	f2 0f 10 74 24 18    	movsd  0x18(%rsp),%xmm6
 a31:	66 0f 28 f8          	movapd %xmm0,%xmm7
 a35:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 a3b:	f2 0f 59 3d 00 00 00 	mulsd  0x0(%rip),%xmm7        # a43 <fasterf+0x63>
 a42:	00 
 a43:	f2 0f 59 35 00 00 00 	mulsd  0x0(%rip),%xmm6        # a4b <fasterf+0x6b>
 a4a:	00 
 a4b:	66 49 0f 7e fe       	movq   %xmm7,%r14
 a50:	f2 0f 11 74 24 20    	movsd  %xmm6,0x20(%rsp)
 a56:	f2 0f 58 0d 00 00 00 	addsd  0x0(%rip),%xmm1        # a5e <fasterf+0x7e>
 a5d:	00 
 a5e:	66 0f 28 d9          	movapd %xmm1,%xmm3
 a62:	f2 0f 11 4c 24 08    	movsd  %xmm1,0x8(%rsp)
 a68:	f2 0f 10 0c 24       	movsd  (%rsp),%xmm1
 a6d:	f2 0f 59 0d 00 00 00 	mulsd  0x0(%rip),%xmm1        # a75 <fasterf+0x95>
 a74:	00 
 a75:	f2 0f 58 cb          	addsd  %xmm3,%xmm1
 a79:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 a7d:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 a81:	0f 8a 3e 01 00 00    	jp     bc5 <fasterf+0x1e5>
 a87:	e8 00 00 00 00       	callq  a8c <fasterf+0xac>
 a8c:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 a92:	f2 0f 11 44 24 28    	movsd  %xmm0,0x28(%rsp)
 a98:	f2 0f 5c 4c 24 10    	subsd  0x10(%rsp),%xmm1
 a9e:	f2 0f 51 c1          	sqrtsd %xmm1,%xmm0
 aa2:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 aa6:	0f 8a 09 01 00 00    	jp     bb5 <fasterf+0x1d5>
 aac:	e8 00 00 00 00       	callq  ab1 <fasterf+0xd1>
 ab1:	66 49 0f 6e ce       	movq   %r14,%xmm1
 ab6:	f2 0f 10 64 24 08    	movsd  0x8(%rsp),%xmm4
 abc:	f2 0f 59 4c 24 10    	mulsd  0x10(%rsp),%xmm1
 ac2:	f2 0f 10 54 24 18    	movsd  0x18(%rsp),%xmm2
 ac8:	f2 0f 59 d4          	mulsd  %xmm4,%xmm2
 acc:	f2 0f 59 4c 24 28    	mulsd  0x28(%rsp),%xmm1
 ad2:	f2 0f 5c ca          	subsd  %xmm2,%xmm1
 ad6:	f2 0f 10 14 24       	movsd  (%rsp),%xmm2
 adb:	f2 0f 59 54 24 20    	mulsd  0x20(%rsp),%xmm2
 ae1:	f2 0f 59 d0          	mulsd  %xmm0,%xmm2
 ae5:	f2 0f 51 c4          	sqrtsd %xmm4,%xmm0
 ae9:	66 0f 2e c0          	ucomisd %xmm0,%xmm0
 aed:	f2 0f 5c ca          	subsd  %xmm2,%xmm1
 af1:	f2 0f 11 0b          	movsd  %xmm1,(%rbx)
 af5:	0f 8a ac 00 00 00    	jp     ba7 <fasterf+0x1c7>
 afb:	e8 00 00 00 00       	callq  b00 <fasterf+0x120>
 b00:	f2 0f 10 6c 24 18    	movsd  0x18(%rsp),%xmm5
 b06:	f2 0f 10 4c 24 10    	movsd  0x10(%rsp),%xmm1
 b0c:	f2 0f 10 54 24 20    	movsd  0x20(%rsp),%xmm2
 b12:	f2 0f 59 cd          	mulsd  %xmm5,%xmm1
 b16:	f2 0f 59 54 24 08    	mulsd  0x8(%rsp),%xmm2
 b1c:	f2 0f 59 c8          	mulsd  %xmm0,%xmm1
 b20:	f2 0f 10 04 24       	movsd  (%rsp),%xmm0
 b25:	f2 0f 59 c5          	mulsd  %xmm5,%xmm0
 b29:	f2 0f 5c ca          	subsd  %xmm2,%xmm1
 b2d:	f2 0f 59 44 24 28    	mulsd  0x28(%rsp),%xmm0
 b33:	f2 0f 5c c8          	subsd  %xmm0,%xmm1
 b37:	f2 0f 11 4d 00       	movsd  %xmm1,0x0(%rbp)
 b3c:	f2 0f 58 0b          	addsd  (%rbx),%xmm1
 b40:	48 83 c4 30          	add    $0x30,%rsp
 b44:	5b                   	pop    %rbx
 b45:	66 0f 28 c1          	movapd %xmm1,%xmm0
 b49:	5d                   	pop    %rbp
 b4a:	41 5e                	pop    %r14
 b4c:	c3                   	retq   
 b4d:	0f 1f 00             	nopl   (%rax)
 b50:	f2 0f 58 c1          	addsd  %xmm1,%xmm0
 b54:	f2 0f 11 4c 24 08    	movsd  %xmm1,0x8(%rsp)
 b5a:	e8 00 00 00 00       	callq  b5f <fasterf+0x17f>
 b5f:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 b65:	66 0f 28 f0          	movapd %xmm0,%xmm6
 b69:	f2 0f 11 44 24 18    	movsd  %xmm0,0x18(%rsp)
 b6f:	f2 0f 10 04 24       	movsd  (%rsp),%xmm0
 b74:	f2 0f 59 35 00 00 00 	mulsd  0x0(%rip),%xmm6        # b7c <fasterf+0x19c>
 b7b:	00 
 b7c:	f2 0f 5c c1          	subsd  %xmm1,%xmm0
 b80:	66 49 0f 7e f6       	movq   %xmm6,%r14
 b85:	e8 00 00 00 00       	callq  b8a <fasterf+0x1aa>
 b8a:	f2 0f 10 3d 00 00 00 	movsd  0x0(%rip),%xmm7        # b92 <fasterf+0x1b2>
 b91:	00 
 b92:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 b98:	f2 0f 59 f8          	mulsd  %xmm0,%xmm7
 b9c:	f2 0f 11 7c 24 20    	movsd  %xmm7,0x20(%rsp)
 ba2:	e9 af fe ff ff       	jmpq   a56 <fasterf+0x76>
 ba7:	66 0f 28 c4          	movapd %xmm4,%xmm0
 bab:	e8 00 00 00 00       	callq  bb0 <fasterf+0x1d0>
 bb0:	e9 46 ff ff ff       	jmpq   afb <fasterf+0x11b>
 bb5:	66 0f 28 c1          	movapd %xmm1,%xmm0
 bb9:	e8 00 00 00 00       	callq  bbe <fasterf+0x1de>
 bbe:	66 90                	xchg   %ax,%ax
 bc0:	e9 e7 fe ff ff       	jmpq   aac <fasterf+0xcc>
 bc5:	66 0f 28 c1          	movapd %xmm1,%xmm0
 bc9:	e8 00 00 00 00       	callq  bce <fasterf+0x1ee>
 bce:	66 90                	xchg   %ax,%ax
 bd0:	e9 b2 fe ff ff       	jmpq   a87 <fasterf+0xa7>
 bd5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
 bdc:	00 00 00 00 

0000000000000be0 <using_fasterf>:
 be0:	41 56                	push   %r14
 be2:	41 55                	push   %r13
 be4:	41 54                	push   %r12
 be6:	55                   	push   %rbp
 be7:	48 89 fd             	mov    %rdi,%rbp
 bea:	53                   	push   %rbx
 beb:	48 83 ec 30          	sub    $0x30,%rsp
 bef:	8b 47 08             	mov    0x8(%rdi),%eax
 bf2:	85 c0                	test   %eax,%eax
 bf4:	0f 8e 1f 01 00 00    	jle    d19 <using_fasterf+0x139>
 bfa:	45 31 e4             	xor    %r12d,%r12d
 bfd:	0f 1f 00             	nopl   (%rax)
 c00:	83 f8 01             	cmp    $0x1,%eax
 c03:	0f 8e 10 01 00 00    	jle    d19 <using_fasterf+0x139>
 c09:	bb 01 00 00 00       	mov    $0x1,%ebx
 c0e:	66 90                	xchg   %ax,%ax
 c10:	44 8d 73 ff          	lea    -0x1(%rbx),%r14d
 c14:	44 89 e2             	mov    %r12d,%edx
 c17:	48 89 ef             	mov    %rbp,%rdi
 c1a:	44 8d 6b 01          	lea    0x1(%rbx),%r13d
 c1e:	44 89 f6             	mov    %r14d,%esi
 c21:	e8 00 00 00 00       	callq  c26 <using_fasterf+0x46>
 c26:	89 de                	mov    %ebx,%esi
 c28:	44 89 e2             	mov    %r12d,%edx
 c2b:	48 89 ef             	mov    %rbp,%rdi
 c2e:	f2 0f 11 44 24 10    	movsd  %xmm0,0x10(%rsp)
 c34:	e8 00 00 00 00       	callq  c39 <using_fasterf+0x59>
 c39:	44 89 e2             	mov    %r12d,%edx
 c3c:	44 89 ee             	mov    %r13d,%esi
 c3f:	48 89 ef             	mov    %rbp,%rdi
 c42:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%rsp)
 c48:	e8 00 00 00 00       	callq  c4d <using_fasterf+0x6d>
 c4d:	f2 0f 10 5c 24 10    	movsd  0x10(%rsp),%xmm3
 c53:	89 da                	mov    %ebx,%edx
 c55:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 c5b:	48 8d 74 24 20       	lea    0x20(%rsp),%rsi
 c60:	66 0f 28 d0          	movapd %xmm0,%xmm2
 c64:	48 8d 7c 24 28       	lea    0x28(%rsp),%rdi
 c69:	66 0f 28 c3          	movapd %xmm3,%xmm0
 c6d:	e8 00 00 00 00       	callq  c72 <using_fasterf+0x92>
 c72:	89 de                	mov    %ebx,%esi
 c74:	44 89 e2             	mov    %r12d,%edx
 c77:	48 89 ef             	mov    %rbp,%rdi
 c7a:	f2 0f 11 44 24 18    	movsd  %xmm0,0x18(%rsp)
 c80:	e8 00 00 00 00       	callq  c85 <using_fasterf+0xa5>
 c85:	f2 0f 10 54 24 20    	movsd  0x20(%rsp),%xmm2
 c8b:	44 89 e2             	mov    %r12d,%edx
 c8e:	44 89 ee             	mov    %r13d,%esi
 c91:	48 89 ef             	mov    %rbp,%rdi
 c94:	f2 0f 58 d0          	addsd  %xmm0,%xmm2
 c98:	f2 0f 11 54 24 10    	movsd  %xmm2,0x10(%rsp)
 c9e:	e8 00 00 00 00       	callq  ca3 <using_fasterf+0xc3>
 ca3:	f2 0f 10 5c 24 18    	movsd  0x18(%rsp),%xmm3
 ca9:	44 89 e2             	mov    %r12d,%edx
 cac:	f2 0f 10 4c 24 28    	movsd  0x28(%rsp),%xmm1
 cb2:	44 89 f6             	mov    %r14d,%esi
 cb5:	48 89 ef             	mov    %rbp,%rdi
 cb8:	f2 0f 58 c8          	addsd  %xmm0,%xmm1
 cbc:	66 0f 28 c3          	movapd %xmm3,%xmm0
 cc0:	f2 0f 58 c3          	addsd  %xmm3,%xmm0
 cc4:	f2 0f 11 4c 24 08    	movsd  %xmm1,0x8(%rsp)
 cca:	e8 00 00 00 00       	callq  ccf <using_fasterf+0xef>
 ccf:	f2 0f 10 54 24 10    	movsd  0x10(%rsp),%xmm2
 cd5:	89 de                	mov    %ebx,%esi
 cd7:	44 89 e2             	mov    %r12d,%edx
 cda:	48 89 ef             	mov    %rbp,%rdi
 cdd:	83 c3 03             	add    $0x3,%ebx
 ce0:	66 0f 28 c2          	movapd %xmm2,%xmm0
 ce4:	e8 00 00 00 00       	callq  ce9 <using_fasterf+0x109>
 ce9:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
 cef:	44 89 e2             	mov    %r12d,%edx
 cf2:	44 89 ee             	mov    %r13d,%esi
 cf5:	48 89 ef             	mov    %rbp,%rdi
 cf8:	66 0f 28 c1          	movapd %xmm1,%xmm0
 cfc:	e8 00 00 00 00       	callq  d01 <using_fasterf+0x121>
 d01:	8b 45 08             	mov    0x8(%rbp),%eax
 d04:	39 d8                	cmp    %ebx,%eax
 d06:	0f 8f 04 ff ff ff    	jg     c10 <using_fasterf+0x30>
 d0c:	41 83 c4 01          	add    $0x1,%r12d
 d10:	44 39 e0             	cmp    %r12d,%eax
 d13:	0f 8f e7 fe ff ff    	jg     c00 <using_fasterf+0x20>
 d19:	48 83 c4 30          	add    $0x30,%rsp
 d1d:	5b                   	pop    %rbx
 d1e:	5d                   	pop    %rbp
 d1f:	41 5c                	pop    %r12
 d21:	41 5d                	pop    %r13
 d23:	41 5e                	pop    %r14
 d25:	c3                   	retq   
 d26:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 d2d:	00 00 00 

0000000000000d30 <register_functions>:
 d30:	48 83 ec 08          	sub    $0x8,%rsp
 d34:	be 00 00 00 00       	mov    $0x0,%esi
 d39:	bf 00 00 00 00       	mov    $0x0,%edi
 d3e:	e8 00 00 00 00       	callq  d43 <register_functions+0x13>
 d43:	be 00 00 00 00       	mov    $0x0,%esi
 d48:	bf 00 00 00 00       	mov    $0x0,%edi
 d4d:	e8 00 00 00 00       	callq  d52 <register_functions+0x22>
 d52:	be 00 00 00 00       	mov    $0x0,%esi
 d57:	bf 00 00 00 00       	mov    $0x0,%edi
 d5c:	48 83 c4 08          	add    $0x8,%rsp
 d60:	e9 00 00 00 00       	jmpq   d65 <register_functions+0x35>
