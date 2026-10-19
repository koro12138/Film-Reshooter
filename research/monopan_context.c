
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0124093c(long *param_1)

{
  uint uVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  undefined4 uVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  uint uVar10;
  ulong uVar11;
  ulong *puVar12;
  long *plVar13;
  int iVar14;
  byte abStack_120 [16];
  undefined8 uStack_110;
  int iStack_104;
  ulong uStack_100;
  ulong uStack_f8;
  ulong uStack_f0;
  ulong uStack_e0;
  ulong uStack_d8;
  ulong uStack_d0;
  ulong auStack_c0 [3];
  code *pcStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  long lStack_48;
  
  lVar2 = tpidr_el0;
  lStack_48 = *(long *)(lVar2 + 0x28);
  puVar12 = (ulong *)param_1[7];
  if ((puVar12 != (ulong *)0x0) && (param_1[2] != 0)) {
    uVar6 = 0xffffffff;
    if (((ulong *)param_1[5] == (ulong *)0x0) || (param_1[3] == 0)) goto LAB_01240dec;
    auStack_c0[0] = 0x1084;
    auStack_c0[1] = *(ulong *)param_1[5];
    uStack_90 = 0;
    uStack_98 = _UNK_0012dac8;
    uStack_a0 = _DAT_0012dac0;
    auStack_c0[2] = 0x40b0;
    pcStack_a8 = FUN_012407ac;
    puVar7 = (undefined8 *)_Znwm(0x20);
    puVar7[1] = 0;
    puVar7[2] = 0;
    *puVar7 = &DAT_01278448;
    uStack_60 = *puVar12;
    uVar8 = FUN_01224c30(auStack_c0,1,&uStack_60,FUN_012407a8,param_1,&uStack_e0);
    uVar11 = uStack_e0;
    iVar14 = (int)uStack_e0;
    plVar13 = (long *)param_1[10];
    puVar7[3] = uVar8;
    param_1[9] = (long)(puVar7 + 3);
    param_1[10] = (long)puVar7;
    if (plVar13 != (long *)0x0) {
      LOAcquire();
      lVar5 = plVar13[1];
      plVar13[1] = lVar5 + -1;
      LORelease();
      if (lVar5 == 0) {
        (**(code **)(*plVar13 + 0x10))(plVar13);
        _ZNSt6__ndk119__shared_weak_count14__release_weakEv(plVar13);
      }
    }
    uVar4 = _UNK_0012d988;
    uVar3 = _DAT_0012d980;
    if (iVar14 == 0) {
      auStack_c0[1] = _UNK_0012d988;
      auStack_c0[0] = _DAT_0012d980;
      pcStack_a8 = (code *)0x0;
      auStack_c0[2] = 0;
      uStack_98 = 0;
      uStack_a0 = 0;
      uStack_88 = 0;
      uStack_90 = 0;
      uStack_78 = 0;
      uStack_80 = 0;
      uStack_68 = 0;
      uStack_70 = 0;
      if (2.0 <= *(float *)(param_1 + 0x19)) {
        uVar10 = *(uint *)(param_1[3] + 4);
        uVar1 = *(uint *)(param_1[3] + 8);
        if ((uVar1 | uVar10) != 0) {
          uVar10 = uVar10 - 1;
          if (uVar10 < 3) {
            pcStack_a8 = *(code **)(&DAT_00d86b48 + (long)(int)uVar10 * 8);
            uVar10 = 4;
            auStack_c0[2] = 0x1097;
          }
          else {
            uVar10 = 2;
          }
          uVar1 = uVar1 - 1;
          if (uVar1 < 3) {
            uVar11 = *(ulong *)(&DAT_00d86b48 + (long)(int)uVar1 * 8);
            uVar1 = uVar10 | 1;
            auStack_c0[uVar10] = 0x1096;
            uVar10 = uVar10 + 2;
            auStack_c0[uVar1] = uVar11;
          }
          auStack_c0[uVar10] = 0;
        }
      }
      iStack_104 = 0;
      uVar8 = FUN_01224ef4(*(undefined8 *)param_1[9],*(undefined8 *)param_1[7],auStack_c0,
                           &iStack_104);
      if (iStack_104 == 0) {
LAB_01240d14:
        iVar14 = 0;
      }
      else {
        uStack_50 = 0;
        uStack_58 = uVar4;
        uStack_60 = uVar3;
        uVar8 = FUN_01224ef4(*(undefined8 *)param_1[9],*(undefined8 *)param_1[7],&uStack_60,
                             &iStack_104);
        if (iStack_104 == 0) goto LAB_01240d14;
        plVar13 = (long *)param_1[10];
        param_1[9] = 0;
        param_1[10] = 0;
        if (plVar13 != (long *)0x0) {
          LOAcquire();
          lVar5 = plVar13[1];
          plVar13[1] = lVar5 + -1;
          LORelease();
          if (lVar5 == 0) {
            (**(code **)(*plVar13 + 0x10))(plVar13);
            _ZNSt6__ndk119__shared_weak_count14__release_weakEv(plVar13);
          }
        }
        FUN_01227b0c(abStack_120,iStack_104);
        puVar12 = (ulong *)_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6insertEmPKc
                                     (abStack_120,0,&DAT_0012a550);
        uStack_f8 = puVar12[1];
        uStack_100 = *puVar12;
        uStack_f0 = puVar12[2];
        puVar12[1] = 0;
        puVar12[2] = 0;
        *puVar12 = 0;
        puVar12 = (ulong *)_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6appendEPKc
                                     (&uStack_100,&DAT_001297cb);
        uStack_d0 = puVar12[2];
        uStack_d8 = puVar12[1];
        uStack_e0 = *puVar12;
        puVar12[1] = 0;
        puVar12[2] = 0;
        *puVar12 = 0;
        if ((uStack_100 & 1) == 0) {
          if ((abStack_120[0] & 1) == 0) goto LAB_01240d04;
LAB_01240d2c:
          _ZdlPv(uStack_110);
          lVar5 = param_1[2];
        }
        else {
          _ZdlPv(uStack_f0);
          if ((abStack_120[0] & 1) != 0) goto LAB_01240d2c;
LAB_01240d04:
          lVar5 = param_1[2];
        }
        if ((lVar5 != 0) && (lVar5 = FUN_00f1d14c(), lVar5 != 0)) {
          uVar9 = FUN_00f1d14c(param_1[2]);
          uVar11 = (ulong)&uStack_e0 | 1;
          if ((uStack_e0 & 1) != 0) {
            uVar11 = uStack_d0;
          }
          FUN_00eeb00c(uVar9,&DAT_001201c0,&DAT_00128837,0x71,uVar11);
        }
        if ((uStack_e0 & 1) != 0) {
          _ZdlPv(uStack_d0);
        }
        iVar14 = -1;
      }
      puVar7 = (undefined8 *)_Znwm(0x20);
      plVar13 = (long *)param_1[0xc];
      puVar7[1] = 0;
      puVar7[2] = 0;
      *puVar7 = &DAT_01278480;
      puVar7[3] = uVar8;
      param_1[0xb] = (long)(puVar7 + 3);
      param_1[0xc] = (long)puVar7;
      if (plVar13 != (long *)0x0) {
        LOAcquire();
        lVar5 = plVar13[1];
        plVar13[1] = lVar5 + -1;
        LORelease();
        if (lVar5 == 0) {
          (**(code **)(*plVar13 + 0x10))(plVar13);
          _ZNSt6__ndk119__shared_weak_count14__release_weakEv(plVar13);
        }
      }
      if (iVar14 == 0) {
        uVar6 = (**(code **)(*param_1 + 0xd0))(param_1,param_1[3] + 0x60);
        goto LAB_01240dec;
      }
      goto LAB_01240de8;
    }
    plVar13 = (long *)param_1[10];
    param_1[9] = 0;
    param_1[10] = 0;
    if (plVar13 != (long *)0x0) {
      LOAcquire();
      lVar5 = plVar13[1];
      plVar13[1] = lVar5 + -1;
      LORelease();
      if (lVar5 == 0) {
        (**(code **)(*plVar13 + 0x10))(plVar13);
        _ZNSt6__ndk119__shared_weak_count14__release_weakEv(plVar13);
      }
    }
    FUN_01227b0c(&uStack_100,uVar11 & 0xffffffff);
    puVar12 = (ulong *)_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6insertEmPKc
                                 (&uStack_100,0,&DAT_001272a2);
    uStack_d8 = puVar12[1];
    uStack_e0 = *puVar12;
    uStack_d0 = puVar12[2];
    puVar12[1] = 0;
    puVar12[2] = 0;
    *puVar12 = 0;
    puVar12 = (ulong *)_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6appendEPKc
                                 (&uStack_e0,&DAT_001297cb);
    uStack_50 = puVar12[2];
    uStack_58 = puVar12[1];
    uStack_60 = *puVar12;
    puVar12[1] = 0;
    puVar12[2] = 0;
    *puVar12 = 0;
    if ((uStack_e0 & 1) == 0) {
      if ((uStack_100 & 1) == 0) goto LAB_01240ae4;
LAB_01240b64:
      _ZdlPv(uStack_f0);
      lVar5 = param_1[2];
    }
    else {
      _ZdlPv(uStack_d0);
      if ((uStack_100 & 1) != 0) goto LAB_01240b64;
LAB_01240ae4:
      lVar5 = param_1[2];
    }
    if ((lVar5 != 0) && (lVar5 = FUN_00f1d14c(), lVar5 != 0)) {
      uVar8 = FUN_00f1d14c(param_1[2]);
      uVar11 = (ulong)&uStack_60 | 1;
      if ((uStack_60 & 1) != 0) {
        uVar11 = uStack_50;
      }
      FUN_00eeb00c(uVar8,&DAT_001201c0,&DAT_00128837,0x53,uVar11);
    }
    if ((uStack_60 & 1) != 0) {
      _ZdlPv(uStack_50);
    }
  }
LAB_01240de8:
  uVar6 = 0xffffffff;
LAB_01240dec:
  lVar5 = FUN_01226dc0(*(undefined8 *)param_1[5],&DAT_001294f9);
  param_1[0x20] = lVar5;
  *(undefined *)(param_1 + 1) = 1;
  FUN_01229898(param_1);
  uVar8 = FUN_00f1d310(param_1[2]);
  lVar5 = FUN_00ee8444(uVar8,2);
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_
            (auStack_c0,lVar5 + 0x10);
  if ((*(byte *)(param_1 + 0x21) & 1) != 0) {
    _ZdlPv(param_1[0x23]);
  }
  param_1[0x22] = auStack_c0[1];
  param_1[0x21] = auStack_c0[0];
  param_1[0x23] = auStack_c0[2];
  if (*(long *)(lVar2 + 0x28) == lStack_48) {
    return uVar6;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


