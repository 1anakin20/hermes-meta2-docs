/* ==================== FUN_1800295a0 @ 1800295a0  (3572 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

Task * FUN_1800295a0(Task *param_1)

{
  PortBase *pPVar1;
  OperationBase *pOVar2;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *this;
  AttributeBase *pAVar3;
  undefined8 *puVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  _State_manager<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
  *p_Var8;
  Task *pTVar9;
  ulonglong uVar10;
  undefined1 auStackY_148 [32];
  PortBase *local_118 [2];
  undefined8 local_108;
  Task *local_100;
  Task *local_f8;
  undefined1 local_f0;
  undefined8 local_e8;
  ulonglong uStack_e0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_d8;
  undefined7 uStack_d7;
  undefined8 local_c8;
  ulonglong uStack_c0;
  undefined **local_b8;
  undefined8 local_b0;
  undefined8 local_a8;
  ulonglong uStack_a0;
  undefined ***local_80;
  undefined **local_78;
  undefined8 local_70;
  undefined8 local_68;
  ulonglong uStack_60;
  undefined ***local_40;
  ulonglong local_38;
  
  local_108 = 0xfffffffffffffffe;
  local_38 = DAT_1802450f8 ^ (ulonglong)auStackY_148;
  local_100 = param_1;
  coco::Task::Task(param_1);
  *(undefined ***)param_1 = meta::blocks::DeviceStreamBlock::vftable;
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_d8,"mono0_OUT",9);
  pPVar1 = (PortBase *)(param_1 + 600);
  local_118[0] = pPVar1;
  coco::PortBase::PortBase(pPVar1,param_1,&local_d8,1,false);
  *(undefined ***)pPVar1 = coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar6 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar6 == (undefined8 *)0x0) {
    puVar6 = (undefined8 *)0x0;
  }
  else {
    puVar6[1] = 0;
    *(undefined1 *)(puVar6 + 1) = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = 0;
    *puVar6 = coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
  }
  puVar4 = *(undefined8 **)(param_1 + 0x260);
  *(undefined8 **)(param_1 + 0x260) = puVar6;
  if (puVar4 != (undefined8 *)0x0) {
    (**(code **)*puVar4)(puVar4,1);
  }
  *(undefined8 *)(param_1 + 0x2b8) = *(undefined8 *)(param_1 + 0x260);
  if (0xf < uStack_c0) {
    uVar5 = CONCAT71(uStack_d7,local_d8);
    uVar10 = uVar5;
    if ((0xfff < uStack_c0 + 1) &&
       (((((byte)local_d8 & 0x1f) != 0 || (uVar10 = *(ulonglong *)(uVar5 - 8), uVar5 <= uVar10)) ||
        (0x1f < (uVar5 - uVar10) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar10);
  }
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_e8 = _DAT_1800a15a0;
  uStack_e0 = _UNK_1800a15a8;
  local_f8 = (Task *)((ulonglong)local_f8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,
             "mono1_OUT",9);
  pPVar1 = (PortBase *)(param_1 + 0x2c0);
  local_118[0] = pPVar1;
  coco::PortBase::PortBase
            (pPVar1,param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,1,false);
  *(undefined ***)pPVar1 = coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar6 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar6 == (undefined8 *)0x0) {
    puVar6 = (undefined8 *)0x0;
  }
  else {
    puVar6[1] = 0;
    *(undefined1 *)(puVar6 + 1) = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = 0;
    *puVar6 = coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
  }
  puVar4 = *(undefined8 **)(param_1 + 0x2c8);
  *(undefined8 **)(param_1 + 0x2c8) = puVar6;
  if (puVar4 != (undefined8 *)0x0) {
    (**(code **)*puVar4)(puVar4,1);
  }
  *(undefined8 *)(param_1 + 800) = *(undefined8 *)(param_1 + 0x2c8);
  if (0xf < uStack_e0) {
    pTVar9 = local_f8;
    if ((0xfff < uStack_e0 + 1) &&
       (((((ulonglong)local_f8 & 0x1f) != 0 ||
         (pTVar9 = *(Task **)((longlong)local_f8 - 8), local_f8 <= pTVar9)) ||
        (0x1f < ((longlong)local_f8 - (longlong)pTVar9) - 8U)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(pTVar9);
  }
  local_e8 = _DAT_1800a15a0;
  uStack_e0 = _UNK_1800a15a8;
  local_f8 = (Task *)((ulonglong)local_f8 & 0xffffffffffffff00);
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_d8,"color_OUT",9);
  pPVar1 = (PortBase *)(param_1 + 0x328);
  local_118[0] = pPVar1;
  coco::PortBase::PortBase(pPVar1,param_1,&local_d8,1,false);
  *(undefined ***)pPVar1 = coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar6 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar6 == (undefined8 *)0x0) {
    puVar6 = (undefined8 *)0x0;
  }
  else {
    puVar6[1] = 0;
    *(undefined1 *)(puVar6 + 1) = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = 0;
    *puVar6 = coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
  }
  puVar4 = *(undefined8 **)(param_1 + 0x330);
  *(undefined8 **)(param_1 + 0x330) = puVar6;
  if (puVar4 != (undefined8 *)0x0) {
    (**(code **)*puVar4)(puVar4,1);
  }
  *(undefined8 *)(param_1 + 0x388) = *(undefined8 *)(param_1 + 0x330);
  if (0xf < uStack_c0) {
    uVar5 = CONCAT71(uStack_d7,local_d8);
    uVar10 = uVar5;
    if ((0xfff < uStack_c0 + 1) &&
       (((((byte)local_d8 & 0x1f) != 0 || (uVar10 = *(ulonglong *)(uVar5 - 8), uVar5 <= uVar10)) ||
        (0x1f < (uVar5 - uVar10) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar10);
  }
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_e8 = _DAT_1800a15a0;
  uStack_e0 = _UNK_1800a15a8;
  local_f8 = (Task *)((ulonglong)local_f8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,
             "point_cloud_OUT",0xf);
  pPVar1 = (PortBase *)(param_1 + 0x390);
  local_118[0] = pPVar1;
  coco::PortBase::PortBase
            (pPVar1,param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,1,false);
  *(undefined ***)pPVar1 = coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar6 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar6 == (undefined8 *)0x0) {
    puVar6 = (undefined8 *)0x0;
  }
  else {
    puVar6[1] = 0;
    *(undefined1 *)(puVar6 + 1) = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = 0;
    *puVar6 = coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
  }
  puVar4 = *(undefined8 **)(param_1 + 0x398);
  *(undefined8 **)(param_1 + 0x398) = puVar6;
  if (puVar4 != (undefined8 *)0x0) {
    (**(code **)*puVar4)(puVar4,1);
  }
  *(undefined8 *)(param_1 + 0x3f0) = *(undefined8 *)(param_1 + 0x398);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_d8,"point_cloud_noise_OUT",0x15);
  coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::
  OutputPort<std::shared_ptr<types::ImageFrame>_>
            ((OutputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x3f8),param_1,&local_d8)
  ;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_d8);
  local_e8 = _DAT_1800a15a0;
  uStack_e0 = _UNK_1800a15a8;
  local_f8 = (Task *)((ulonglong)local_f8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,
             "point_cloud_confidence_OUT",0x1a);
  coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::
  OutputPort<std::shared_ptr<types::ImageFrame>_>
            ((OutputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x460),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign(&local_d8,"ir_OUT",6)
  ;
  coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::
  OutputPort<std::shared_ptr<types::ImageFrame>_>
            ((OutputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x4c8),param_1,&local_d8)
  ;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_d8);
  local_e8 = _DAT_1800a15a0;
  uStack_e0 = _UNK_1800a15a8;
  local_f8 = (Task *)((ulonglong)local_f8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,
             "depth_OUT",9);
  coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::
  OutputPort<std::shared_ptr<types::ImageFrame>_>
            ((OutputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x530),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_d8,"imu0_acc_OUT",0xc);
  coco::OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
  OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>
            ((OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_> *)(param_1 + 0x598),
             param_1,&local_d8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_d8);
  local_e8 = _DAT_1800a15a0;
  uStack_e0 = _UNK_1800a15a8;
  local_f8 = (Task *)((ulonglong)local_f8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,
             "imu0_gyro_OUT",0xd);
  coco::OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
  OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>
            ((OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_> *)(param_1 + 0x600),
             param_1,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_d8,"imu1_acc_OUT",0xc);
  coco::OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
  OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>
            ((OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_> *)(param_1 + 0x668),
             param_1,&local_d8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_d8);
  local_e8 = _DAT_1800a15a0;
  uStack_e0 = _UNK_1800a15a8;
  local_f8 = (Task *)((ulonglong)local_f8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,
             "imu1_gyro_OUT",0xd);
  coco::OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
  OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>
            ((OutputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_> *)(param_1 + 0x6d0),
             param_1,(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_d8,"xml_calibration_OUT",0x13);
  pPVar1 = (PortBase *)(param_1 + 0x738);
  local_118[0] = pPVar1;
  coco::PortBase::PortBase(pPVar1,param_1,&local_d8,1,false);
  *(undefined ***)pPVar1 =
       coco::
       OutputPort<std::shared_ptr<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
       ::vftable;
  puVar6 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar6 == (undefined8 *)0x0) {
    puVar6 = (undefined8 *)0x0;
  }
  else {
    puVar6[1] = 0;
    *(undefined1 *)(puVar6 + 1) = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = 0;
    *puVar6 = coco::
              ConnectionManagerOutputDefault<std::shared_ptr<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
              ::vftable;
  }
  puVar4 = *(undefined8 **)(param_1 + 0x740);
  *(undefined8 **)(param_1 + 0x740) = puVar6;
  if (puVar4 != (undefined8 *)0x0) {
    (**(code **)*puVar4)(puVar4,1);
  }
  *(undefined8 *)(param_1 + 0x798) = *(undefined8 *)(param_1 + 0x740);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_d8);
  local_e8 = _DAT_1800a15a0;
  uStack_e0 = _UNK_1800a15a8;
  local_f8 = (Task *)((ulonglong)local_f8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,
             "audio_OUT",9);
  pPVar1 = (PortBase *)(param_1 + 0x7a0);
  local_118[0] = pPVar1;
  coco::PortBase::PortBase
            (pPVar1,param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,1,false);
  *(undefined ***)pPVar1 = coco::OutputPort<std::shared_ptr<types::AudioData>_>::vftable;
  puVar6 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar6 == (undefined8 *)0x0) {
    puVar6 = (undefined8 *)0x0;
  }
  else {
    puVar6[1] = 0;
    *(undefined1 *)(puVar6 + 1) = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = 0;
    *puVar6 = coco::ConnectionManagerOutputDefault<std::shared_ptr<types::AudioData>_>::vftable;
  }
  puVar4 = *(undefined8 **)(param_1 + 0x7a8);
  *(undefined8 **)(param_1 + 0x7a8) = puVar6;
  if (puVar4 != (undefined8 *)0x0) {
    (**(code **)*puVar4)(puVar4,1);
  }
  *(undefined8 *)(param_1 + 0x800) = *(undefined8 *)(param_1 + 0x7a8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_d8,"buttons_OUT",0xb);
  pPVar1 = (PortBase *)(param_1 + 0x808);
  local_118[0] = pPVar1;
  coco::PortBase::PortBase(pPVar1,param_1,&local_d8,1,false);
  *(undefined ***)pPVar1 = coco::OutputPort<std::shared_ptr<device::ButtonData>_>::vftable;
  puVar6 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar6 == (undefined8 *)0x0) {
    puVar6 = (undefined8 *)0x0;
  }
  else {
    puVar6[1] = 0;
    *(undefined1 *)(puVar6 + 1) = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = 0;
    *puVar6 = coco::ConnectionManagerOutputDefault<std::shared_ptr<device::ButtonData>_>::vftable;
  }
  puVar4 = *(undefined8 **)(param_1 + 0x810);
  *(undefined8 **)(param_1 + 0x810) = puVar6;
  if (puVar4 != (undefined8 *)0x0) {
    (**(code **)*puVar4)(puVar4,1);
  }
  *(undefined8 *)(param_1 + 0x868) = *(undefined8 *)(param_1 + 0x810);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_d8);
  *(undefined8 *)(param_1 + 0x870) = 0;
  param_1[0x878] = (Task)0x0;
  std::promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
            ((promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> *)
             (param_1 + 0x880));
  *(undefined8 *)(param_1 + 0x898) = 0;
  param_1[0x8a0] = (Task)0x0;
  std::promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
            ((promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> *)
             (param_1 + 0x8a8));
  *(undefined4 *)(param_1 + 0x8c0) = 1;
  *(undefined4 *)(param_1 + 0x8c4) = 2;
  *(undefined8 *)(param_1 + 0x8c8) = 0;
  *(undefined8 *)(param_1 + 0x8d0) = 0;
  *(undefined8 *)(param_1 + 0x8d8) = 0;
  *(undefined8 *)(param_1 + 0x8e0) = 0;
  *(undefined8 *)(param_1 + 0x8e8) = 0;
  *(undefined4 *)(param_1 + 0x8f0) = 0x10e;
  *(undefined8 *)(param_1 + 0x908) = 0;
  *(undefined8 *)(param_1 + 0x910) = 0xf;
  *(basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(param_1 + 0x8f8) =
       (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(param_1 + 0x8f8),
             "MODE_5_60FPS_300",0x10);
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_d8,"GetCalibrationXml",0x11);
  coco::
  Operation<class_std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>___cdecl(void)>
  ::
  Operation<class_std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>___cdecl(void)><class_std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_(__cdecl_meta::blocks::DeviceStreamBlock::*)(void)const___ptr64,meta::blocks::DeviceStreamBlock*___ptr64>
            ((Operation<class_std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>___cdecl(void)>
              *)(param_1 + 0x918),param_1,&local_d8,
             meta::blocks::DeviceStreamBlock::GetCalibrationXml,(DeviceStreamBlock *)param_1);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_d8);
  local_e8 = _DAT_1800a15a0;
  uStack_e0 = _UNK_1800a15a8;
  local_f8 = (Task *)((ulonglong)local_f8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,
             "GetSerialNumber",0xf);
  coco::
  Operation<class_std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>___cdecl(void)>
  ::
  Operation<class_std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>___cdecl(void)><class_std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_(__cdecl_meta::blocks::DeviceStreamBlock::*)(void)const___ptr64,meta::blocks::DeviceStreamBlock*___ptr64>
            ((Operation<class_std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>___cdecl(void)>
              *)(param_1 + 0x9a0),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8,
             meta::blocks::DeviceStreamBlock::GetSerialNumber,(DeviceStreamBlock *)param_1);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_f8);
  local_68 = _DAT_1800a15a0;
  uStack_60 = _UNK_1800a15a8;
  local_78 = (undefined **)((ulonglong)local_78 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_78,
             "GetDeviceStatus",0xf);
  pOVar2 = (OperationBase *)(param_1 + 0xa28);
  local_118[0] = (PortBase *)pOVar2;
  puVar6 = (undefined8 *)
           utils::bind_this<device::DeviceStatus,meta::blocks::DeviceStreamBlock>
                     ((_func_DeviceStatus *)&local_d8,
                      (DeviceStreamBlock *)meta::blocks::DeviceStreamBlock::GetDeviceStatus);
  local_b8 = std::
             _Func_impl_no_alloc<std::_Binder<std::_Unforced,enum_device::DeviceStatus_(__cdecl_meta::blocks::DeviceStreamBlock::*&___ptr64)(void)const___ptr64,meta::blocks::DeviceStreamBlock*___ptr64&___ptr64>,device::DeviceStatus>
             ::vftable;
  local_b0 = *puVar6;
  local_a8 = puVar6[1];
  local_80 = &local_b8;
  coco::OperationBase::OperationBase
            (pOVar2,param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_78);
  *(undefined ***)pOVar2 = coco::Operation<enum_device::DeviceStatus___cdecl(void)>::vftable;
  local_f8 = param_1 + 0xa70;
  *(undefined8 *)(param_1 + 0xaa8) = 0;
  if (local_80 != (undefined ***)0x0) {
    uVar7 = (*(code *)**local_80)(local_80,local_f8);
    *(undefined8 *)(param_1 + 0xaa8) = uVar7;
  }
  if (local_80 != (undefined ***)0x0) {
    (*(code *)(*local_80)[4])
              (local_80,CONCAT71((int7)((ulonglong)&local_b8 >> 8),local_80 != &local_b8));
  }
  *(undefined ***)pOVar2 = coco::Operation<enum_device::DeviceStatus___cdecl(void)>::vftable;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_78);
  local_a8 = _DAT_1800a15a0;
  uStack_a0 = _UNK_1800a15a8;
  local_b8 = (undefined **)((ulonglong)local_b8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_b8,
             "GetConnectionStatus",0x13);
  pOVar2 = (OperationBase *)(param_1 + 0xab0);
  local_f8 = (Task *)pOVar2;
  puVar6 = (undefined8 *)
           utils::bind_this<device::ConnectionStatus,meta::blocks::DeviceStreamBlock>
                     ((_func_ConnectionStatus *)&local_d8,
                      (DeviceStreamBlock *)meta::blocks::DeviceStreamBlock::GetConnectionStatus);
  local_78 = std::
             _Func_impl_no_alloc<std::_Binder<std::_Unforced,enum_device::ConnectionStatus_(__cdecl_meta::blocks::DeviceStreamBlock::*&___ptr64)(void)const___ptr64,meta::blocks::DeviceStreamBlock*___ptr64&___ptr64>,device::ConnectionStatus>
             ::vftable;
  local_70 = *puVar6;
  local_68 = puVar6[1];
  local_40 = &local_78;
  coco::OperationBase::OperationBase
            (pOVar2,param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_b8);
  *(undefined ***)pOVar2 = coco::Operation<enum_device::ConnectionStatus___cdecl(void)>::vftable;
  local_118[0] = (PortBase *)(param_1 + 0xaf8);
  *(undefined8 *)(param_1 + 0xb30) = 0;
  if (local_40 != (undefined ***)0x0) {
    uVar7 = (*(code *)**local_40)(local_40,local_118[0]);
    *(undefined8 *)(param_1 + 0xb30) = uVar7;
  }
  if (local_40 != (undefined ***)0x0) {
    (*(code *)(*local_40)[4])
              (local_40,CONCAT71((int7)((ulonglong)&local_78 >> 8),local_40 != &local_78));
  }
  *(undefined ***)pOVar2 = coco::Operation<enum_device::ConnectionStatus___cdecl(void)>::vftable;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_b8);
  param_1[0xb38] = (Task)0x0;
  local_68 = _DAT_1800a15a0;
  uStack_60 = _UNK_1800a15a8;
  local_78 = (undefined **)((ulonglong)local_78 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_78,
             "all_spectre_filtering",0x15);
  coco::Attribute<bool>::Attribute<bool>
            ((Attribute<bool> *)(param_1 + 0xb40),param_1,&local_78,param_1 + 0xb38);
  param_1[0xbd8] = (Task)0x1;
  local_a8 = _DAT_1800a15a0;
  uStack_a0 = _UNK_1800a15a8;
  local_b8 = (undefined **)((ulonglong)local_b8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_b8,
             "enable_depth",0xc);
  coco::Attribute<bool>::Attribute<bool>
            ((Attribute<bool> *)(param_1 + 0xbe0),param_1,&local_b8,param_1 + 0xbd8);
  param_1[0xc78] = (Task)0x0;
  local_68 = _DAT_1800a15a0;
  uStack_60 = _UNK_1800a15a8;
  local_78 = (undefined **)((ulonglong)local_78 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_78,
             "enable_audio",0xc);
  coco::Attribute<bool>::Attribute<bool>
            ((Attribute<bool> *)(param_1 + 0xc80),param_1,&local_78,param_1 + 0xc78);
  param_1[0xd18] = (Task)0x0;
  local_a8 = _DAT_1800a15a0;
  uStack_a0 = _UNK_1800a15a8;
  local_b8 = (undefined **)((ulonglong)local_b8 & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&local_b8,
             "enable_royale_recording",0x17);
  coco::Attribute<bool>::Attribute<bool>
            ((Attribute<bool> *)(param_1 + 0xd20),param_1,&local_b8,param_1 + 0xd18);
  this = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(param_1 + 0xdb8);
  *(undefined8 *)(param_1 + 0xdc8) = 0;
  *(undefined8 *)(param_1 + 0xdd0) = 0xf;
  *this = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign(this,"",0);
  local_c8 = _DAT_1800a15a0;
  uStack_c0 = _UNK_1800a15a8;
  local_d8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_d8,"royale_recording_filename",0x19);
  local_f8 = (Task *)&local_d8;
  pAVar3 = (AttributeBase *)(param_1 + 0xdd8);
  local_80 = (undefined ***)0x0;
  local_118[0] = (PortBase *)pAVar3;
  coco::AttributeBase::AttributeBase(pAVar3,param_1,&local_d8,&local_b8);
  *(undefined ***)pAVar3 =
       coco::Attribute<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
       vftable;
  *(basic_string<char,std::char_traits<char>,std::allocator<char>_> **)(param_1 + 0xe68) = this;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_d8);
  p_Var8 = (_State_manager<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
            *)std::promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
              get_future((promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
                          *)(param_1 + 0x880));
  local_f8 = (Task *)0x0;
  std::_State_manager<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  _Move_from((_State_manager<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
              *)&local_f8,p_Var8);
  local_f0 = 0;
  std::_State_manager<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  _Move_from((_State_manager<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
              *)(param_1 + 0x870),
             (_State_manager<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
              *)&local_f8);
  std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  ~shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
            ((shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> *
             )&local_f8);
  std::future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  ~future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
            ((future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> *)
             local_118);
  p_Var8 = (_State_manager<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
            *)std::promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
              get_future((promise<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
                          *)(param_1 + 0x8a8));
  local_f8 = (Task *)0x0;
  std::_State_manager<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  _Move_from((_State_manager<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
              *)&local_f8,p_Var8);
  local_f0 = 0;
  std::_State_manager<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  _Move_from((_State_manager<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
              *)(param_1 + 0x898),
             (_State_manager<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
              *)&local_f8);
  std::shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  ~shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
            ((shared_future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> *
             )&local_f8);
  std::future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  ~future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
            ((future<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> *)
             local_118);
  return param_1;
}


/* ==================== FUN_18007d2a0 @ 18007d2a0  (2811 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

DeviceStreamBlock * FUN_18007d2a0(DeviceStreamBlock *param_1)

{
  undefined8 *puVar1;
  ulonglong uVar2;
  undefined8 *puVar3;
  ulonglong uVar4;
  undefined1 auStack_c8 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_80;
  undefined7 uStack_7f;
  undefined8 local_70;
  ulonglong uStack_68;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_60;
  undefined7 uStack_5f;
  undefined8 local_50;
  ulonglong uStack_48;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_40;
  undefined7 uStack_3f;
  undefined8 local_30;
  ulonglong uStack_28;
  ulonglong local_20;
  
  local_20 = DAT_1802450f8 ^ (ulonglong)auStack_c8;
  meta::blocks::DeviceStreamBlock::DeviceStreamBlock(param_1);
  *(undefined ***)param_1 = meta::blocks::MockDeviceStreamBlock::vftable;
  local_30 = _DAT_1800a15a0;
  uStack_28 = _UNK_1800a15a8;
  local_40 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_40,"mono0_IN",8);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0xe70),(Task *)param_1,&local_40,0,true);
  *(undefined ***)(param_1 + 0xe70) = coco::InputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar3 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *(undefined1 *)(puVar3 + 1) = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *puVar3 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar3[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0xe78);
  *(undefined8 **)(param_1 + 0xe78) = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0xed0) = *(undefined8 *)(param_1 + 0xe78);
  if (0xf < uStack_28) {
    uVar2 = CONCAT71(uStack_3f,local_40);
    uVar4 = uVar2;
    if ((0xfff < uStack_28 + 1) &&
       (((((byte)local_40 & 0x1f) != 0 || (uVar4 = *(ulonglong *)(uVar2 - 8), uVar2 <= uVar4)) ||
        (0x1f < (uVar2 - uVar4) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar4);
  }
  local_30 = _DAT_1800a15a0;
  uStack_28 = _UNK_1800a15a8;
  local_40 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_80,"mono1_IN",8);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0xed8),(Task *)param_1,&local_80,0,true);
  *(undefined ***)(param_1 + 0xed8) = coco::InputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar3 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *(undefined1 *)(puVar3 + 1) = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *puVar3 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar3[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0xee0);
  *(undefined8 **)(param_1 + 0xee0) = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0xf38) = *(undefined8 *)(param_1 + 0xee0);
  if (0xf < uStack_68) {
    uVar2 = CONCAT71(uStack_7f,local_80);
    uVar4 = uVar2;
    if ((0xfff < uStack_68 + 1) &&
       (((((byte)local_80 & 0x1f) != 0 || (uVar4 = *(ulonglong *)(uVar2 - 8), uVar2 <= uVar4)) ||
        (0x1f < (uVar2 - uVar4) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar4);
  }
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_30 = _DAT_1800a15a0;
  uStack_28 = _UNK_1800a15a8;
  local_40 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_40,"color_IN",8);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0xf40),(Task *)param_1,&local_40,0,true);
  *(undefined ***)(param_1 + 0xf40) = coco::InputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar3 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *(undefined1 *)(puVar3 + 1) = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *puVar3 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar3[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0xf48);
  *(undefined8 **)(param_1 + 0xf48) = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 4000) = *(undefined8 *)(param_1 + 0xf48);
  if (0xf < uStack_28) {
    uVar2 = CONCAT71(uStack_3f,local_40);
    uVar4 = uVar2;
    if ((0xfff < uStack_28 + 1) &&
       (((((byte)local_40 & 0x1f) != 0 || (uVar4 = *(ulonglong *)(uVar2 - 8), uVar2 <= uVar4)) ||
        (0x1f < (uVar2 - uVar4) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar4);
  }
  local_30 = _DAT_1800a15a0;
  uStack_28 = _UNK_1800a15a8;
  local_40 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign(&local_80,"ir_IN",5);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0xfa8),(Task *)param_1,&local_80,0,true);
  *(undefined ***)(param_1 + 0xfa8) = coco::InputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar3 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *(undefined1 *)(puVar3 + 1) = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *puVar3 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar3[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0xfb0);
  *(undefined8 **)(param_1 + 0xfb0) = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x1008) = *(undefined8 *)(param_1 + 0xfb0);
  if (0xf < uStack_68) {
    uVar2 = CONCAT71(uStack_7f,local_80);
    uVar4 = uVar2;
    if ((0xfff < uStack_68 + 1) &&
       (((((byte)local_80 & 0x1f) != 0 || (uVar4 = *(ulonglong *)(uVar2 - 8), uVar2 <= uVar4)) ||
        (0x1f < (uVar2 - uVar4) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar4);
  }
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_30 = _DAT_1800a15a0;
  uStack_28 = _UNK_1800a15a8;
  local_40 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_40,"depth_IN",8);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0x1010),(Task *)param_1,&local_40,0,true);
  *(undefined ***)(param_1 + 0x1010) = coco::InputPort<std::shared_ptr<types::ImageFrame>_>::vftable
  ;
  puVar3 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *(undefined1 *)(puVar3 + 1) = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *puVar3 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar3[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x1018);
  *(undefined8 **)(param_1 + 0x1018) = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x1070) = *(undefined8 *)(param_1 + 0x1018);
  if (0xf < uStack_28) {
    uVar2 = CONCAT71(uStack_3f,local_40);
    uVar4 = uVar2;
    if ((0xfff < uStack_28 + 1) &&
       (((((byte)local_40 & 0x1f) != 0 || (uVar4 = *(ulonglong *)(uVar2 - 8), uVar2 <= uVar4)) ||
        (0x1f < (uVar2 - uVar4) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar4);
  }
  local_30 = _DAT_1800a15a0;
  uStack_28 = _UNK_1800a15a8;
  local_40 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_50 = _DAT_1800a15a0;
  uStack_48 = _UNK_1800a15a8;
  local_60 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_60,"point_cloud_IN",0xe);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0x1078),(Task *)param_1,&local_60,0,true);
  *(undefined ***)(param_1 + 0x1078) = coco::InputPort<std::shared_ptr<types::ImageFrame>_>::vftable
  ;
  puVar3 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *(undefined1 *)(puVar3 + 1) = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *puVar3 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar3[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x1080);
  *(undefined8 **)(param_1 + 0x1080) = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x10d8) = *(undefined8 *)(param_1 + 0x1080);
  if (0xf < uStack_48) {
    std::_Deallocate((void *)CONCAT71(uStack_5f,local_60),uStack_48 + 1,1);
  }
  local_50 = _DAT_1800a15a0;
  uStack_48 = _UNK_1800a15a8;
  local_60 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_80,"point_cloud_noise_IN",0x14);
  coco::InputPort<std::shared_ptr<types::ImageFrame>_>::
  InputPort<std::shared_ptr<types::ImageFrame>_>
            ((InputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x10e0),(Task *)param_1,
             &local_80,true);
  if (0xf < uStack_68) {
    std::allocator<char>::deallocate
              ((allocator<char> *)&local_80,(char *)CONCAT71(uStack_7f,local_80),uStack_68 + 1);
  }
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_30 = _DAT_1800a15a0;
  uStack_28 = _UNK_1800a15a8;
  local_40 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_40,"point_cloud_confidence_IN",0x19);
  coco::InputPort<std::shared_ptr<types::ImageFrame>_>::
  InputPort<std::shared_ptr<types::ImageFrame>_>
            ((InputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x1148),(Task *)param_1,
             &local_40,true);
  if (0xf < uStack_28) {
    std::allocator<char>::deallocate
              ((allocator<char> *)&local_40,(char *)CONCAT71(uStack_3f,local_40),uStack_28 + 1);
  }
  local_30 = _DAT_1800a15a0;
  uStack_28 = _UNK_1800a15a8;
  local_40 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_80,"imu0_acc_IN",0xb);
  coco::InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
  InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>
            ((InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_> *)(param_1 + 0x11b0),
             (Task *)param_1,&local_80,true);
  if (0xf < uStack_68) {
    std::allocator<char>::deallocate
              ((allocator<char> *)&local_80,(char *)CONCAT71(uStack_7f,local_80),uStack_68 + 1);
  }
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_50 = _DAT_1800a15a0;
  uStack_48 = _UNK_1800a15a8;
  local_60 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_60,"imu0_gyro_IN",0xc);
  coco::InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
  InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>
            ((InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_> *)(param_1 + 0x1218),
             (Task *)param_1,&local_60,true);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_60);
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_80,"imu1_acc_IN",0xb);
  coco::InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
  InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>
            ((InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_> *)(param_1 + 0x1280),
             (Task *)param_1,&local_80,true);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_80);
  local_50 = _DAT_1800a15a0;
  uStack_48 = _UNK_1800a15a8;
  local_60 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_60,"imu1_gyro_IN",0xc);
  coco::InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
  InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>
            ((InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_> *)(param_1 + 0x12e8),
             (Task *)param_1,&local_60,true);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_60);
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_80,"audio_IN",8);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0x1350),(Task *)param_1,&local_80,0,true);
  *(undefined ***)(param_1 + 0x1350) = coco::InputPort<std::shared_ptr<types::AudioData>_>::vftable;
  puVar3 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *(undefined1 *)(puVar3 + 1) = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *puVar3 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::AudioData>_>::vftable;
    puVar3[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x1358);
  *(undefined8 **)(param_1 + 0x1358) = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x13b0) = *(undefined8 *)(param_1 + 0x1358);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_80);
  local_50 = _DAT_1800a15a0;
  uStack_48 = _UNK_1800a15a8;
  local_60 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_60,"buttons_IN",10);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0x13b8),(Task *)param_1,&local_60,0,true);
  *(undefined ***)(param_1 + 0x13b8) =
       coco::InputPort<std::shared_ptr<device::ButtonData>_>::vftable;
  puVar3 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *(undefined1 *)(puVar3 + 1) = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *puVar3 = coco::ConnectionManagerInputDefault<std::shared_ptr<device::ButtonData>_>::vftable;
    puVar3[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x13c0);
  *(undefined8 **)(param_1 + 0x13c0) = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x1418) = *(undefined8 *)(param_1 + 0x13c0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_60);
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_80,"serial_number_IN",0x10);
  coco::
  InputPort<std::shared_ptr<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
  ::
  InputPort<std::shared_ptr<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
            ((InputPort<std::shared_ptr<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
              *)(param_1 + 0x1420),(Task *)param_1,&local_80,true);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_80);
  local_50 = _DAT_1800a15a0;
  uStack_48 = _UNK_1800a15a8;
  local_60 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_60,"xml_calibration_IN",0x12);
  coco::
  InputPort<std::shared_ptr<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
  ::
  InputPort<std::shared_ptr<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
            ((InputPort<std::shared_ptr<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>
              *)(param_1 + 0x1488),(Task *)param_1,&local_60,true);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_60);
  *(undefined8 *)(param_1 + 0x1500) = 0;
  *(undefined8 *)(param_1 + 0x1508) = 0xf;
  param_1[0x14f0] = (DeviceStreamBlock)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(param_1 + 0x14f0),
             "",0);
  local_50 = _DAT_1800a15a0;
  uStack_48 = _UNK_1800a15a8;
  local_60 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_60,"royale_playback_filename",0x18);
  coco::Attribute<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>::
  Attribute<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>
            ((Attribute<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_> *)
             (param_1 + 0x1510),param_1,&local_60,param_1 + 0x14f0);
  param_1[0x15a8] = (DeviceStreamBlock)0x0;
  local_70 = _DAT_1800a15a0;
  uStack_68 = _UNK_1800a15a8;
  local_80 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_80,"enable_royale_playback",0x16);
  coco::Attribute<bool>::Attribute<bool>
            ((Attribute<bool> *)(param_1 + 0x15b0),param_1,&local_80,param_1 + 0x15a8);
  param_1[0x1648] = (DeviceStreamBlock)0x0;
  local_50 = _DAT_1800a15a0;
  uStack_48 = _UNK_1800a15a8;
  local_60 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_60,"loop_royale_playback",0x14);
  coco::Attribute<bool>::Attribute<bool>
            ((Attribute<bool> *)(param_1 + 0x1650),param_1,&local_60,param_1 + 0x1648);
  return param_1;
}


/* ==================== FUN_180042ef0 @ 180042ef0  (1469 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_180042ef0(longlong param_1)

{
  __uint64 *p_Var1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  LogMessage *pLVar5;
  basic_ostream<char,std::char_traits<char>_> *pbVar6;
  undefined8 uVar7;
  basicString<char> *pbVar8;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar9;
  Variant *pVVar10;
  Pair<royale::ProcessingFlag,royale::Variant> *pPVar11;
  undefined8 *puVar12;
  code *pcVar13;
  undefined1 auStack_118 [32];
  basicString<char> local_f8 [48];
  Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_> local_c8 [48];
  undefined8 local_98;
  code *local_90 [2];
  longlong local_80;
  ulonglong uStack_78;
  ProcessingFlag local_70;
  undefined4 uStack_6c;
  hardware_error local_50 [56];
  ulonglong local_18;
  
  local_98 = 0xfffffffffffffffe;
  local_18 = DAT_1802450f8 ^ (ulonglong)auStack_118;
  if (*(longlong **)(param_1 + 0x8c8) == (longlong *)0x0) {
    pcVar4 = (char *)FUN_180043dd0(local_90);
    pLVar5 = (LogMessage *)
             google::LogMessage::LogMessage
                       ((LogMessage *)&local_70,
                        "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                        ,0x18b,2);
    pbVar6 = google::LogMessage::stream(pLVar5);
    p_Var1 = (__uint64 *)(pcVar4 + 0x10);
    if (0xf < *(ulonglong *)(pcVar4 + 0x18)) {
      pcVar4 = *(char **)pcVar4;
    }
    pbVar6 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                       ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,pcVar4,*p_Var1)
    ;
    std::operator<<<std::char_traits<char>_>
              ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,
               "Failed to create ToF camera device");
    google::LogMessage::~LogMessage((LogMessage *)&local_70);
    if (0xf < uStack_78) {
      pcVar13 = local_90[0];
      if ((0xfff < uStack_78 + 1) &&
         (((((ulonglong)local_90[0] & 0x1f) != 0 ||
           (pcVar13 = *(code **)(local_90[0] + -8), local_90[0] <= pcVar13)) ||
          ((code *)0x1f < local_90[0] + (-8 - (longlong)pcVar13))))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_180002658(pcVar13);
    }
    uVar7 = 0;
  }
  else {
    iVar3 = (**(code **)(**(longlong **)(param_1 + 0x8c8) + 0x10))();
    if (iVar3 != 0) {
      pbVar8 = (basicString<char> *)royale::getErrorString((CameraStatus)local_f8);
      pcVar4 = royale::basicString<char>::c_str(pbVar8);
      std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
      basic_string<char,std::char_traits<char>,std::allocator<char>_>
                ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_90,pcVar4)
      ;
      royale::basicString<char>::~basicString<char>(local_f8);
      pbVar9 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
               std::operator+<char,std::char_traits<char>,std::allocator<char>_>
                         ((char *)&local_70,
                          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)"Cannot initialize the camera device error code: ");
      fou::except::hardware_error::hardware_error(local_50,pbVar9);
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(local_50,(ThrowInfo *)&DAT_1800c4050);
    }
    royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
    Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(local_c8);
    local_70 = 0xd;
    pVVar10 = (Variant *)royale::Variant::Variant((Variant *)local_90,*(bool *)(param_1 + 0xb38));
    pPVar11 = (Pair<royale::ProcessingFlag,royale::Variant> *)
              royale::Pair<royale::ProcessingFlag,royale::Variant>::
              Pair<royale::ProcessingFlag,royale::Variant>
                        ((Pair<royale::ProcessingFlag,royale::Variant> *)local_f8,&local_70,pVVar10)
    ;
    royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::push_back
              (local_c8,pPVar11);
    royale::Pair<royale::ProcessingFlag,royale::Variant>::
    ~Pair<royale::ProcessingFlag,royale::Variant>
              ((Pair<royale::ProcessingFlag,royale::Variant> *)local_f8);
    royale::Variant::~Variant((Variant *)local_90);
    local_70 = 0xf;
    pVVar10 = (Variant *)royale::Variant::Variant((Variant *)local_90,*(bool *)(param_1 + 0xb38));
    pPVar11 = (Pair<royale::ProcessingFlag,royale::Variant> *)
              royale::Pair<royale::ProcessingFlag,royale::Variant>::
              Pair<royale::ProcessingFlag,royale::Variant>
                        ((Pair<royale::ProcessingFlag,royale::Variant> *)local_f8,&local_70,pVVar10)
    ;
    royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::push_back
              (local_c8,pPVar11);
    royale::Pair<royale::ProcessingFlag,royale::Variant>::
    ~Pair<royale::ProcessingFlag,royale::Variant>
              ((Pair<royale::ProcessingFlag,royale::Variant> *)local_f8);
    royale::Variant::~Variant((Variant *)local_90);
    iVar3 = (**(code **)(**(longlong **)(param_1 + 0x8c8) + 0x1c8))
                      (*(longlong **)(param_1 + 0x8c8),local_c8);
    if (iVar3 == 0) {
      local_90[0] = meta::blocks::DeviceStreamBlock::TofDataGrabber;
      local_80 = param_1;
      puVar12 = (undefined8 *)
                std::
                make_unique<RoyaleDataListener,std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void>
                          ((_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
                            *)&local_70);
      uVar7 = *puVar12;
      *puVar12 = 0;
      puVar12 = *(undefined8 **)(param_1 + 0x8d0);
      *(undefined8 *)(param_1 + 0x8d0) = uVar7;
      if (puVar12 != (undefined8 *)0x0) {
        (**(code **)*puVar12)(puVar12,1);
      }
      puVar12 = (undefined8 *)CONCAT44(uStack_6c,local_70);
      if (puVar12 != (undefined8 *)0x0) {
        (**(code **)*puVar12)(puVar12,1);
      }
      iVar3 = (**(code **)(**(longlong **)(param_1 + 0x8c8) + 0xa0))
                        (*(longlong **)(param_1 + 0x8c8),*(undefined8 *)(param_1 + 0x8d0));
      if (iVar3 == 0) {
        iVar3 = (**(code **)(**(longlong **)(param_1 + 0x8c8) + 0xf0))();
        if (iVar3 == 0) {
          royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
          ~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(local_c8);
          uVar7 = 1;
        }
        else {
          pbVar8 = (basicString<char> *)royale::getErrorString((CameraStatus)local_f8);
          pcVar4 = (char *)FUN_180043dd0(local_90);
          pLVar5 = (LogMessage *)
                   google::LogMessage::LogMessage
                             ((LogMessage *)&local_70,
                              "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                              ,0x1b6,2);
          pbVar6 = google::LogMessage::stream(pLVar5);
          p_Var1 = (__uint64 *)(pcVar4 + 0x10);
          if (0xf < *(ulonglong *)(pcVar4 + 0x18)) {
            pcVar4 = *(char **)pcVar4;
          }
          pbVar6 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                             ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,pcVar4,
                              *p_Var1);
          pbVar6 = std::operator<<<std::char_traits<char>_>
                             ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,
                              "Cannot start capture. ERROR: ");
          royale::operator<<<char>
                    ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,pbVar8);
          google::LogMessage::~LogMessage((LogMessage *)&local_70);
          if (0xf < uStack_78) {
            pcVar13 = local_90[0];
            if ((0xfff < uStack_78 + 1) &&
               (((((ulonglong)local_90[0] & 0x1f) != 0 ||
                 (pcVar13 = *(code **)(local_90[0] + -8), local_90[0] <= pcVar13)) ||
                ((code *)0x1f < local_90[0] + (-8 - (longlong)pcVar13))))) {
                    /* WARNING: Subroutine does not return */
              _invalid_parameter_noinfo_noreturn();
            }
            FUN_180002658(pcVar13);
          }
          local_80 = _DAT_1800a15a0;
          uStack_78 = _UNK_1800a15a8;
          local_90[0] = (code *)((ulonglong)local_90[0] & 0xffffffffffffff00);
          royale::basicString<char>::~basicString<char>(local_f8);
          royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
          ~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(local_c8);
          uVar7 = 0;
        }
      }
      else {
        pbVar8 = (basicString<char> *)royale::getErrorString((CameraStatus)local_f8);
        pcVar4 = (char *)FUN_180043dd0(local_90);
        pLVar5 = (LogMessage *)
                 google::LogMessage::LogMessage
                           ((LogMessage *)&local_70,
                            "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                            ,0x1af,2);
        pbVar6 = google::LogMessage::stream(pLVar5);
        p_Var1 = (__uint64 *)(pcVar4 + 0x10);
        if (0xf < *(ulonglong *)(pcVar4 + 0x18)) {
          pcVar4 = *(char **)pcVar4;
        }
        pbVar6 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                           ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,pcVar4,
                            *p_Var1);
        pbVar6 = std::operator<<<std::char_traits<char>_>
                           ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,
                            "Cant Register Data Listener. ERROR:  ");
        royale::operator<<<char>
                  ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,pbVar8);
        google::LogMessage::~LogMessage((LogMessage *)&local_70);
        if (0xf < uStack_78) {
          pcVar13 = local_90[0];
          if ((0xfff < uStack_78 + 1) &&
             (((((ulonglong)local_90[0] & 0x1f) != 0 ||
               (pcVar13 = *(code **)(local_90[0] + -8), local_90[0] <= pcVar13)) ||
              ((code *)0x1f < local_90[0] + (-8 - (longlong)pcVar13))))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          FUN_180002658(pcVar13);
        }
        local_80 = _DAT_1800a15a0;
        uStack_78 = _UNK_1800a15a8;
        local_90[0] = (code *)((ulonglong)local_90[0] & 0xffffffffffffff00);
        royale::basicString<char>::~basicString<char>(local_f8);
        royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
        ~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(local_c8);
        uVar7 = 0;
      }
    }
    else {
      pbVar8 = (basicString<char> *)royale::getErrorString((CameraStatus)local_f8);
      pcVar4 = (char *)FUN_180043dd0(local_90);
      pLVar5 = (LogMessage *)
               google::LogMessage::LogMessage
                         ((LogMessage *)&local_70,
                          "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                          ,0x1a4,2);
      pbVar6 = google::LogMessage::stream(pLVar5);
      p_Var1 = (__uint64 *)(pcVar4 + 0x10);
      if (0xf < *(ulonglong *)(pcVar4 + 0x18)) {
        pcVar4 = *(char **)pcVar4;
      }
      pbVar6 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                         ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,pcVar4,
                          *p_Var1);
      pbVar6 = std::operator<<<std::char_traits<char>_>
                         ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,
                          "Bad Processing Parameters. ERROR: ");
      bVar2 = royale::basicString<char>::empty(pbVar8);
      if (!bVar2) {
        pcVar4 = royale::basicString<char>::c_str(pbVar8);
        std::operator<<<std::char_traits<char>_>
                  ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar6,pcVar4);
      }
      google::LogMessage::~LogMessage((LogMessage *)&local_70);
      if (0xf < uStack_78) {
        pcVar13 = local_90[0];
        if ((0xfff < uStack_78 + 1) &&
           (((((ulonglong)local_90[0] & 0x1f) != 0 ||
             (pcVar13 = *(code **)(local_90[0] + -8), local_90[0] <= pcVar13)) ||
            ((code *)0x1f < local_90[0] + (-8 - (longlong)pcVar13))))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        FUN_180002658(pcVar13);
      }
      local_80 = _DAT_1800a15a0;
      uStack_78 = _UNK_1800a15a8;
      local_90[0] = (code *)((ulonglong)local_90[0] & 0xffffffffffffff00);
      royale::basicString<char>::~basicString<char>(local_f8);
      royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
      ~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(local_c8);
      uVar7 = 0;
    }
  }
  return uVar7;
}


/* ==================== FUN_180070200 @ 180070200  (4636 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

Task * FUN_180070200(Task *param_1)

{
  _Hash<std::_Umap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,std::_Uhash_compare<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>,0>_>
  *this;
  OperationBase *this_00;
  undefined8 *puVar1;
  _List_node<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
  *p_Var2;
  _List_node<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
  *p_Var3;
  ulonglong uVar4;
  undefined8 *puVar5;
  _List_node<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
  *p_Var6;
  undefined8 uVar7;
  _List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
  *p_Var8;
  ulonglong uVar9;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar10;
  undefined1 auStack_428 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_3e0;
  undefined7 uStack_3df;
  undefined8 local_3d0;
  ulonglong uStack_3c8;
  _List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
  *local_3c0 [2];
  undefined8 local_3b0;
  ulonglong uStack_3a8;
  undefined **local_398;
  undefined8 local_390;
  undefined8 local_388;
  undefined ***local_360;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_358 [16];
  undefined8 local_348;
  ulonglong uStack_340;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_338 [16];
  undefined8 local_328;
  ulonglong uStack_320;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_318 [16];
  undefined8 local_308;
  ulonglong uStack_300;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_2f8 [16];
  undefined8 local_2e8;
  ulonglong uStack_2e0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_2d8 [16];
  undefined8 local_2c8;
  ulonglong uStack_2c0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_2b8 [16];
  undefined8 local_2a8;
  ulonglong uStack_2a0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_298 [16];
  undefined8 local_288;
  ulonglong uStack_280;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_278 [16];
  undefined8 local_268;
  ulonglong uStack_260;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_258 [16];
  undefined8 local_248;
  ulonglong uStack_240;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_238 [16];
  undefined8 local_228;
  ulonglong uStack_220;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_218 [16];
  undefined8 local_208;
  ulonglong uStack_200;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_1f8 [16];
  undefined8 local_1e8;
  ulonglong uStack_1e0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_1d8 [16];
  undefined8 local_1c8;
  ulonglong uStack_1c0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_1b8 [16];
  undefined8 local_1a8;
  ulonglong uStack_1a0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_198 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_178 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_158 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_138 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_118 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_f8 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_d8 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_b8 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_98 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_78 [32];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_58 [32];
  ulonglong local_38 [2];
  
  local_38[0] = DAT_1802450f8 ^ (ulonglong)auStack_428;
  coco::Task::Task(param_1);
  *(undefined ***)param_1 = meta::blocks::DeviceStatusBlock::vftable;
  *(undefined4 *)(param_1 + 600) = 0;
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"imu0_acc_IN",0xb);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0x260),param_1,&local_3e0,0,false);
  *(undefined ***)(param_1 + 0x260) =
       coco::InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::vftable;
  puVar5 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar5 == (undefined8 *)0x0) {
    puVar5 = (undefined8 *)0x0;
  }
  else {
    puVar5[1] = 0;
    *(undefined1 *)(puVar5 + 1) = 0;
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    *puVar5 = coco::
              ConnectionManagerInputDefault<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
              vftable;
    puVar5[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x268);
  *(undefined8 **)(param_1 + 0x268) = puVar5;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x2c0) = *(undefined8 *)(param_1 + 0x268);
  if (0xf < uStack_3c8) {
    uVar4 = CONCAT71(uStack_3df,local_3e0);
    uVar9 = uVar4;
    if ((0xfff < uStack_3c8 + 1) &&
       (((((byte)local_3e0 & 0x1f) != 0 || (uVar9 = *(ulonglong *)(uVar4 - 8), uVar4 <= uVar9)) ||
        (0x1f < (uVar4 - uVar9) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar9);
  }
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "imu0_gyro_IN",0xc);
  coco::PortBase::PortBase
            ((PortBase *)(param_1 + 0x2c8),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,0,false);
  *(undefined ***)(param_1 + 0x2c8) =
       coco::InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::vftable;
  puVar5 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar5 == (undefined8 *)0x0) {
    puVar5 = (undefined8 *)0x0;
  }
  else {
    puVar5[1] = 0;
    *(undefined1 *)(puVar5 + 1) = 0;
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    *puVar5 = coco::
              ConnectionManagerInputDefault<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
              vftable;
    puVar5[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x2d0);
  *(undefined8 **)(param_1 + 0x2d0) = puVar5;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x328) = *(undefined8 *)(param_1 + 0x2d0);
  if (0xf < uStack_3a8) {
    p_Var8 = local_3c0[0];
    if ((0xfff < uStack_3a8 + 1) &&
       (((((ulonglong)local_3c0[0] & 0x1f) != 0 ||
         (p_Var8 = *(_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                     **)(local_3c0[0] + -8), local_3c0[0] <= p_Var8)) ||
        ((_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
          *)0x1f < local_3c0[0] + (-8 - (longlong)p_Var8))))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(p_Var8);
  }
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"imu1_acc_IN",0xb);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0x330),param_1,&local_3e0,0,false);
  *(undefined ***)(param_1 + 0x330) =
       coco::InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::vftable;
  puVar5 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar5 == (undefined8 *)0x0) {
    puVar5 = (undefined8 *)0x0;
  }
  else {
    puVar5[1] = 0;
    *(undefined1 *)(puVar5 + 1) = 0;
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    *puVar5 = coco::
              ConnectionManagerInputDefault<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
              vftable;
    puVar5[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x338);
  *(undefined8 **)(param_1 + 0x338) = puVar5;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x390) = *(undefined8 *)(param_1 + 0x338);
  if (0xf < uStack_3c8) {
    uVar4 = CONCAT71(uStack_3df,local_3e0);
    uVar9 = uVar4;
    if ((0xfff < uStack_3c8 + 1) &&
       (((((byte)local_3e0 & 0x1f) != 0 || (uVar9 = *(ulonglong *)(uVar4 - 8), uVar4 <= uVar9)) ||
        (0x1f < (uVar4 - uVar9) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar9);
  }
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "imu1_gyro_IN",0xc);
  coco::PortBase::PortBase
            ((PortBase *)(param_1 + 0x398),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,0,false);
  *(undefined ***)(param_1 + 0x398) =
       coco::InputPort<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::vftable;
  puVar5 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar5 == (undefined8 *)0x0) {
    puVar5 = (undefined8 *)0x0;
  }
  else {
    puVar5[1] = 0;
    *(undefined1 *)(puVar5 + 1) = 0;
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    *puVar5 = coco::
              ConnectionManagerInputDefault<std::shared_ptr<types::MatrixStamped<short,3,1>_>_>::
              vftable;
    puVar5[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x3a0);
  *(undefined8 **)(param_1 + 0x3a0) = puVar5;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x3f8) = *(undefined8 *)(param_1 + 0x3a0);
  if (0xf < uStack_3a8) {
    p_Var8 = local_3c0[0];
    if ((0xfff < uStack_3a8 + 1) &&
       (((((ulonglong)local_3c0[0] & 0x1f) != 0 ||
         (p_Var8 = *(_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                     **)(local_3c0[0] + -8), local_3c0[0] <= p_Var8)) ||
        ((_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
          *)0x1f < local_3c0[0] + (-8 - (longlong)p_Var8))))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(p_Var8);
  }
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"mono0_IN",8);
  coco::PortBase::PortBase((PortBase *)(param_1 + 0x400),param_1,&local_3e0,0,false);
  *(undefined ***)(param_1 + 0x400) = coco::InputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar5 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar5 == (undefined8 *)0x0) {
    puVar5 = (undefined8 *)0x0;
  }
  else {
    puVar5[1] = 0;
    *(undefined1 *)(puVar5 + 1) = 0;
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    *puVar5 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar5[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x408);
  *(undefined8 **)(param_1 + 0x408) = puVar5;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x460) = *(undefined8 *)(param_1 + 0x408);
  if (0xf < uStack_3c8) {
    uVar4 = CONCAT71(uStack_3df,local_3e0);
    uVar9 = uVar4;
    if ((0xfff < uStack_3c8 + 1) &&
       (((((byte)local_3e0 & 0x1f) != 0 || (uVar9 = *(ulonglong *)(uVar4 - 8), uVar4 <= uVar9)) ||
        (0x1f < (uVar4 - uVar9) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar9);
  }
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,"mono1_IN"
             ,8);
  coco::PortBase::PortBase
            ((PortBase *)(param_1 + 0x468),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,0,false);
  *(undefined ***)(param_1 + 0x468) = coco::InputPort<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar5 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar5 == (undefined8 *)0x0) {
    puVar5 = (undefined8 *)0x0;
  }
  else {
    puVar5[1] = 0;
    *(undefined1 *)(puVar5 + 1) = 0;
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    *puVar5 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar5[5] = 0;
  }
  puVar1 = *(undefined8 **)(param_1 + 0x470);
  *(undefined8 **)(param_1 + 0x470) = puVar5;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(param_1 + 0x4c8) = *(undefined8 *)(param_1 + 0x470);
  if (0xf < uStack_3a8) {
    std::allocator<char>::deallocate
              ((allocator<char> *)local_3c0,(char *)local_3c0[0],uStack_3a8 + 1);
  }
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"color_IN",8);
  coco::InputPort<std::shared_ptr<types::ImageFrame>_>::
  InputPort<std::shared_ptr<types::ImageFrame>_>
            ((InputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x4d0),param_1,&local_3e0,
             false);
  if (0xf < uStack_3c8) {
    std::allocator<char>::deallocate
              ((allocator<char> *)&local_3e0,(char *)CONCAT71(uStack_3df,local_3e0),uStack_3c8 + 1);
  }
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "point_cloud_IN",0xe);
  coco::InputPort<std::shared_ptr<types::ImageFrame>_>::
  InputPort<std::shared_ptr<types::ImageFrame>_>
            ((InputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x538),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,false);
  if (0xf < uStack_3a8) {
    std::allocator<char>::deallocate
              ((allocator<char> *)local_3c0,(char *)local_3c0[0],uStack_3a8 + 1);
  }
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign(&local_3e0,"ir_IN",5)
  ;
  coco::InputPort<std::shared_ptr<types::ImageFrame>_>::
  InputPort<std::shared_ptr<types::ImageFrame>_>
            ((InputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x5a0),param_1,&local_3e0,
             false);
  if (0xf < uStack_3c8) {
    std::allocator<char>::deallocate
              ((allocator<char> *)&local_3e0,(char *)CONCAT71(uStack_3df,local_3e0),uStack_3c8 + 1);
  }
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,"depth_IN"
             ,8);
  coco::InputPort<std::shared_ptr<types::ImageFrame>_>::
  InputPort<std::shared_ptr<types::ImageFrame>_>
            ((InputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x608),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,false);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"point_cloud_noise_IN",0x14);
  coco::InputPort<std::shared_ptr<types::ImageFrame>_>::
  InputPort<std::shared_ptr<types::ImageFrame>_>
            ((InputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x670),param_1,&local_3e0,
             false);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_3e0)
  ;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "point_cloud_confidence_IN",0x19);
  coco::InputPort<std::shared_ptr<types::ImageFrame>_>::
  InputPort<std::shared_ptr<types::ImageFrame>_>
            ((InputPort<std::shared_ptr<types::ImageFrame>_> *)(param_1 + 0x6d8),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,false);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"imu0_acc_fps_OUT",0x10);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0x740),param_1,&local_3e0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_3e0)
  ;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "imu0_gyro_fps_OUT",0x11);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0x7a8),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"imu1_acc_fps_OUT",0x10);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0x810),param_1,&local_3e0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_3e0)
  ;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "imu1_gyro_fps_OUT",0x11);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0x878),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"mono0_fps_OUT",0xd);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0x8e0),param_1,&local_3e0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_3e0)
  ;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "mono1_fps_OUT",0xd);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0x948),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"color_fps_OUT",0xd);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0x9b0),param_1,&local_3e0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_3e0)
  ;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "point_cloud_fps_OUT",0x13);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0xa18),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"ir_fps_OUT",10);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0xa80),param_1,&local_3e0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_3e0)
  ;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "depth_fps_OUT",0xd);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0xae8),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (&local_3e0,"point_cloud_noise_fps_OUT",0x19);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 0xb50),param_1,&local_3e0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_3e0)
  ;
  local_3b0 = _DAT_1800a15a0;
  uStack_3a8 = _UNK_1800a15a8;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)((ulonglong)local_3c0[0] & 0xffffffffffffff00);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0,
             "point_cloud_confidence_fps_OUT",0x1e);
  coco::OutputPort<double>::OutputPort<double>
            ((OutputPort<double> *)(param_1 + 3000),param_1,
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_3c0);
  local_328 = _DAT_1800a15a0;
  uStack_320 = _UNK_1800a15a8;
  local_338[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_338,"imu0_acc_IN",0xb);
  local_308 = _DAT_1800a15a0;
  uStack_300 = _UNK_1800a15a8;
  local_318[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_318,"imu0_acc_fps_OUT",0x10);
  local_2e8 = _DAT_1800a15a0;
  uStack_2e0 = _UNK_1800a15a8;
  local_2f8[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_2f8,"imu0_gyro_IN",0xc);
  local_2c8 = _DAT_1800a15a0;
  uStack_2c0 = _UNK_1800a15a8;
  local_2d8[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_2d8,"imu0_gyro_fps_OUT",0x11);
  local_2a8 = _DAT_1800a15a0;
  uStack_2a0 = _UNK_1800a15a8;
  local_2b8[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_2b8,"imu1_acc_IN",0xb);
  local_288 = _DAT_1800a15a0;
  uStack_280 = _UNK_1800a15a8;
  local_298[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_298,"imu1_acc_fps_OUT",0x10);
  local_268 = _DAT_1800a15a0;
  uStack_260 = _UNK_1800a15a8;
  local_278[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_278,"imu1_gyro_IN",0xc);
  local_248 = _DAT_1800a15a0;
  uStack_240 = _UNK_1800a15a8;
  local_258[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_258,"imu1_gyro_fps_OUT",0x11);
  local_228 = _DAT_1800a15a0;
  uStack_220 = _UNK_1800a15a8;
  local_238[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_238,"mono0_IN",8);
  local_208 = _DAT_1800a15a0;
  uStack_200 = _UNK_1800a15a8;
  local_218[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_218,"mono0_fps_OUT",0xd);
  local_1e8 = _DAT_1800a15a0;
  uStack_1e0 = _UNK_1800a15a8;
  local_1f8[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_1f8,"mono1_IN",8);
  local_1c8 = _DAT_1800a15a0;
  uStack_1c0 = _UNK_1800a15a8;
  local_1d8[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_1d8,"mono1_fps_OUT",0xd);
  local_1a8 = _DAT_1800a15a0;
  uStack_1a0 = _UNK_1800a15a8;
  local_1b8[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_1b8,"color_IN",8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_198,"color_fps_OUT");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_178,"point_cloud_IN");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_158,"point_cloud_fps_OUT");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_138,"ir_IN");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_118,"ir_fps_OUT");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_f8,"depth_IN");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_d8,"depth_fps_OUT");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_b8,"point_cloud_noise_IN");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>
            (local_98,"point_cloud_noise_fps_OUT");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>
            (local_78,"point_cloud_confidence_IN");
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>
            (local_58,"point_cloud_confidence_fps_OUT");
  this = (_Hash<std::_Umap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,std::_Uhash_compare<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>,0>_>
          *)(param_1 + 0xc20);
  *(undefined4 *)this = 0;
  p_Var8 = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
            *)(param_1 + 0xc28);
  *(undefined8 *)p_Var8 = 0;
  *(undefined8 *)(param_1 + 0xc30) = 0;
  local_3c0[0] = p_Var8;
  p_Var6 = std::
           _List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
           ::_Buynode0(p_Var8,(_List_node<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
                               *)0x0,
                       (_List_node<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
                        *)0x0);
  *(_List_node<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
    **)p_Var8 = p_Var6;
  *(undefined8 *)(param_1 + 0xc38) = 0;
  *(undefined8 *)(param_1 + 0xc40) = 0;
  *(undefined8 *)(param_1 + 0xc48) = 0;
  *(undefined4 *)this = 0x3f800000;
  std::
  _Hash<std::_Umap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,std::_Uhash_compare<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>,0>_>
  ::_Init(this,8);
  pbVar10 = local_338;
  do {
    p_Var2 = (_List_node<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
              *)**(undefined8 **)p_Var8;
    p_Var3 = *(_List_node<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
               **)(p_Var2 + 8);
    p_Var6 = std::
             _List_buy<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>
             ::
             _Buynode<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_const&___ptr64>
                       ((_List_buy<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>
                         *)p_Var8,p_Var2,p_Var3,
                        (pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
                         *)pbVar10);
    if (*(longlong *)(param_1 + 0xc30) == 0x333333333333332) {
                    /* WARNING: Subroutine does not return */
      std::_Xlength_error("list<T> too long");
    }
    *(longlong *)(param_1 + 0xc30) = *(longlong *)(param_1 + 0xc30) + 1;
    *(_List_node<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
      **)(p_Var2 + 8) = p_Var6;
    *(_List_node<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,void*___ptr64>
      **)p_Var3 = p_Var6;
    std::
    _Hash<std::_Umap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,std::_Uhash_compare<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>,0>_>
    ::
    _Insert<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>&___ptr64,std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>_>
              (this,local_3c0,**(longlong **)p_Var8 + 0x10);
    pbVar10 = pbVar10 + 0x40;
  } while (pbVar10 != (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)local_38);
  _eh_vector_destructor_iterator_
            (local_338,0x40,0xc,
             std::
             pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
             ::
             ~pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
            );
  local_348 = _DAT_1800a15a0;
  uStack_340 = _UNK_1800a15a8;
  local_358[0] = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign
            (local_358,"GetStreamingStatus",0x12);
  this_00 = (OperationBase *)(param_1 + 0xc60);
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)this_00;
  puVar5 = (undefined8 *)
           utils::bind_this<long,meta::blocks::DeviceStatusBlock>
                     ((_func_long *)&local_3e0,
                      (DeviceStatusBlock *)meta::blocks::DeviceStatusBlock::GetStreamingStatus);
  local_398 = std::
              _Func_impl_no_alloc<std::_Binder<std::_Unforced,long_(__cdecl_meta::blocks::DeviceStatusBlock::*&___ptr64)(void)___ptr64,meta::blocks::DeviceStatusBlock*___ptr64&___ptr64>,long>
              ::vftable;
  local_390 = *puVar5;
  local_388 = puVar5[1];
  local_360 = &local_398;
  coco::OperationBase::OperationBase(this_00,param_1,local_358);
  *(undefined ***)this_00 = coco::Operation<long___cdecl(void)>::vftable;
  *(undefined8 *)(param_1 + 0xce0) = 0;
  if (local_360 != (undefined ***)0x0) {
    uVar7 = (*(code *)**local_360)(local_360,param_1 + 0xca8);
    *(undefined8 *)(param_1 + 0xce0) = uVar7;
  }
  if (local_360 != (undefined ***)0x0) {
    (*(code *)(*local_360)[4])
              (local_360,CONCAT71((int7)((ulonglong)&local_398 >> 8),local_360 != &local_398));
  }
  *(undefined ***)this_00 = coco::Operation<long___cdecl(void)>::vftable;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(local_358);
  *(undefined4 *)(param_1 + 0xce8) = 0;
  param_1[0xcec] = (Task)0x0;
  param_1[0xced] = (Task)0x0;
  local_3d0 = _DAT_1800a15a0;
  uStack_3c8 = _UNK_1800a15a8;
  local_3e0 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::assign(&local_3e0,"debug",5)
  ;
  local_3c0[0] = (_List_alloc<std::_List_base_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>_>_>
                  *)&local_3e0;
  local_360 = (undefined ***)0x0;
  coco::AttributeBase::AttributeBase
            ((AttributeBase *)(param_1 + 0xcf0),param_1,&local_3e0,&local_398);
  *(undefined ***)(param_1 + 0xcf0) = coco::Attribute<bool>::vftable;
  *(Task **)(param_1 + 0xd80) = param_1 + 0xced;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate(&local_3e0)
  ;
  *(undefined4 *)(param_1 + 0xd88) = 0x1e;
  *(undefined4 *)(param_1 + 0xd8c) = 0x14;
  *(undefined4 *)(param_1 + 0xd90) = 0x1e;
  *(undefined8 *)(param_1 + 0xd94) = 100;
  *(undefined4 *)(param_1 + 0xd9c) = 1;
  *(undefined4 *)(param_1 + 0xda0) = 2;
  *(undefined4 *)(param_1 + 0xda4) = 3;
  *(undefined4 *)(param_1 + 0xda8) = 4;
  *(undefined4 *)(param_1 + 0xdac) = 5;
  *(undefined4 *)(param_1 + 0xdb0) = 6;
  *(undefined4 *)(param_1 + 0xdb4) = 7;
  *(undefined4 *)(param_1 + 0xdb8) = 8;
  *(undefined4 *)(param_1 + 0xdbc) = 9;
  *(undefined4 *)(param_1 + 0xdc0) = 10;
  *(undefined4 *)(param_1 + 0xdc4) = 0xb;
  *(undefined4 *)(param_1 + 0xdc8) = 0xc;
  return param_1;
}


/* ==================== FUN_1800460c0 @ 1800460c0  (2586 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800460c0(DeviceStreamBlock *param_1)

{
  __uint64 *p_Var1;
  DeviceStreamBlock *pDVar2;
  _Ref_count_base *p_Var3;
  SAQDriverManagerAdapterCls *pSVar4;
  undefined8 *puVar5;
  longlong *plVar6;
  ulonglong uVar7;
  bool bVar8;
  int iVar9;
  uint uVar10;
  __uint64 _Var11;
  char *pcVar12;
  LogMessage *pLVar13;
  basic_ostream<char,std::char_traits<char>_> *pbVar14;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar15;
  DeviceStreamBlock *pDVar16;
  undefined8 uVar17;
  basicString<char> *pbVar18;
  ApplicationManager *pAVar19;
  longlong lVar20;
  longlong lVar21;
  ulonglong uVar22;
  DeviceStreamBlock *pDVar23;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar24;
  uint uVar25;
  undefined1 auStack_3c8 [32];
  undefined4 local_3a8;
  uint local_398;
  CameraManager local_390 [8];
  undefined8 *local_388;
  undefined8 local_380;
  undefined8 uStack_378;
  undefined8 local_370;
  LogMessage local_368 [16];
  LogMessage local_358 [16];
  LogMessage local_348 [16];
  LogMessage local_338 [16];
  LogMessage local_328 [16];
  Vector<royale::basicString<char>_> local_318 [48];
  basicString<char> local_2e8 [48];
  basicString<char> local_2b8 [48];
  basicString<char> local_288 [48];
  basicString<char> local_258 [48];
  basicString<char> local_228 [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_1f8;
  undefined7 uStack_1f7;
  longlong local_1e8;
  ulonglong uStack_1e0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_1d8;
  undefined7 uStack_1d7;
  __uint64 local_1c8;
  ulonglong local_1c0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_1b8;
  undefined7 uStack_1b7;
  longlong local_1a8;
  ulonglong uStack_1a0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_198;
  undefined7 uStack_197;
  longlong local_188;
  ulonglong uStack_180;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_178;
  undefined7 uStack_177;
  longlong local_168;
  ulonglong uStack_160;
  byte local_158;
  undefined7 uStack_157;
  longlong local_148;
  ulonglong uStack_140;
  byte local_138;
  undefined7 uStack_137;
  longlong local_128;
  ulonglong uStack_120;
  ulonglong local_118 [3];
  ulonglong local_100;
  ulonglong local_f8 [3];
  ulonglong local_e0;
  ulonglong local_d8 [3];
  ulonglong local_c0;
  hardware_error local_b8 [56];
  undefined1 local_80 [32];
  char local_60 [32];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [32];
  ulonglong local_20;
  
  local_370 = 0xfffffffffffffffe;
  local_20 = DAT_1802450f8 ^ (ulonglong)auStack_3c8;
  local_398 = 0;
  royale::basicString<char>::basicString<char>(local_2e8,"d79dab562f13ef8373e906d919aec323a2857388")
  ;
  royale::CameraManager::CameraManager(local_390,local_2e8);
  royale::basicString<char>::~basicString<char>(local_2e8);
  local_380 = 0;
  uStack_378 = 0;
  p_Var3 = *(_Ref_count_base **)(param_1 + 0x8e0);
  pSVar4 = *(SAQDriverManagerAdapterCls **)(param_1 + 0x8d8);
  uVar25 = 0;
  if (p_Var3 != (_Ref_count_base *)0x0) {
    LOCK();
    *(int *)(p_Var3 + 8) = *(int *)(p_Var3 + 8) + 1;
    UNLOCK();
    uVar25 = local_398;
  }
  std::_Ptr_base<sdc::SAQDriverManagerAdapterCls>::_Reset0
            ((_Ptr_base<sdc::SAQDriverManagerAdapterCls> *)&local_380,pSVar4,p_Var3);
  royale::CameraManager::getConnectedCameraList(local_390,local_318,&local_380);
  _Var11 = royale::Vector<royale::basicString<char>_>::size(local_318);
  if (_Var11 == 0) {
    pcVar12 = (char *)FUN_180043dd0(local_118);
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (local_368,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x141,2);
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    std::operator<<<std::char_traits<char>_>
              ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
               "No depth camera detected.");
    google::LogMessage::~LogMessage(local_368);
    if (0xf < local_100) {
      uVar22 = local_118[0];
      if ((0xfff < local_100 + 1) &&
         ((((local_118[0] & 0x1f) != 0 ||
           (uVar22 = *(ulonglong *)(local_118[0] - 8), local_118[0] <= uVar22)) ||
          (0x1f < (local_118[0] - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_180002658(uVar22);
    }
    royale::Vector<royale::basicString<char>_>::~Vector<royale::basicString<char>_>(local_318);
    royale::CameraManager::~CameraManager(local_390);
    return;
  }
  if (1 < _Var11) {
    std::to_string((__uint64)local_80);
    pcVar12 = (char *)std::operator+<char,std::char_traits<char>,std::allocator<char>_>
                                (local_60,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                           *)"Expected 1, detected ");
    pbVar15 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
              std::operator+<char,std::char_traits<char>,std::allocator<char>_>(local_40,pcVar12);
    fou::except::hardware_error::hardware_error(local_b8,pbVar15);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_b8,(ThrowInfo *)&DAT_1800c4050);
  }
  royale::Vector<royale::basicString<char>_>::operator[](local_318,0);
  pDVar16 = (DeviceStreamBlock *)
            royale::CameraManager::createCamera(local_390,(basicString<char> *)&local_388);
  pDVar2 = param_1 + 0x8c8;
  if (pDVar2 != pDVar16) {
    lVar20 = *(longlong *)pDVar16;
    *(longlong *)pDVar16 = 0;
    puVar5 = *(undefined8 **)pDVar2;
    *(longlong *)pDVar2 = lVar20;
    if (puVar5 != (undefined8 *)0x0) {
      (**(code **)*puVar5)(puVar5,1);
    }
  }
  if (local_388 != (undefined8 *)0x0) {
    (**(code **)*local_388)(local_388,1);
  }
  if (-1 < *(int *)FLAGS_v_exref) {
    pcVar12 = (char *)FUN_180043dd0(local_f8);
    local_398 = 1;
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (local_358,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x14b);
    uVar25 = 3;
    local_398 = 3;
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    std::operator<<<std::char_traits<char>_>
              ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,"Tof Camera Detected.."
              );
  }
  if ((uVar25 & 2) != 0) {
    uVar25 = uVar25 & 0xfffffffd;
    google::LogMessage::~LogMessage(local_358);
  }
  if (((uVar25 & 1) != 0) && (uVar25 = uVar25 & 0xfffffffe, 0xf < local_e0)) {
    uVar22 = local_f8[0];
    if ((0xfff < local_e0 + 1) &&
       ((((local_f8[0] & 0x1f) != 0 ||
         (uVar22 = *(ulonglong *)(local_f8[0] - 8), local_f8[0] <= uVar22)) ||
        (0x1f < (local_f8[0] - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  royale::Vector<royale::basicString<char>_>::~Vector<royale::basicString<char>_>(local_318);
  royale::CameraManager::~CameraManager(local_390);
  bVar8 = meta::blocks::DeviceStreamBlock::InitializeTof(param_1);
  if (!bVar8) {
    return;
  }
  plVar6 = *(longlong **)pDVar2;
  pDVar16 = param_1 + 0x8f8;
  pDVar23 = pDVar16;
  if (0xf < *(ulonglong *)(param_1 + 0x910)) {
    pDVar23 = *(DeviceStreamBlock **)pDVar16;
  }
  uVar17 = royale::basicString<char>::basicString<char>(local_288,(char *)pDVar23);
  iVar9 = (**(code **)(*plVar6 + 0x48))(plVar6,uVar17);
  royale::basicString<char>::~basicString<char>(local_288);
  if (iVar9 != 0) {
    pbVar18 = (basicString<char> *)royale::getErrorString((CameraStatus)local_258);
    pcVar12 = (char *)FUN_180043dd0(&local_158);
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (local_348,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x157,2);
    if (0xf < *(ulonglong *)(param_1 + 0x910)) {
      pDVar16 = *(DeviceStreamBlock **)pDVar16;
    }
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    pbVar14 = std::operator<<<std::char_traits<char>_>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
                         "Cant set use case ");
    pbVar14 = std::operator<<<std::char_traits<char>_>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
                         (char *)pDVar16);
    pbVar14 = std::operator<<<std::char_traits<char>_>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,". ERROR: ");
    royale::operator<<<char>((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pbVar18);
    google::LogMessage::~LogMessage(local_348);
    if (0xf < uStack_140) {
      uVar7 = CONCAT71(uStack_157,local_158);
      uVar22 = uVar7;
      if ((0xfff < uStack_140 + 1) &&
         ((((local_158 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22)) ||
          (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_180002658(uVar22);
    }
    local_148 = _DAT_1800a15a0;
    uStack_140 = _UNK_1800a15a8;
    local_158 = 0;
    royale::basicString<char>::~basicString<char>(local_258);
    return;
  }
  iVar9 = (**(code **)(**(longlong **)pDVar2 + 0x70))
                    (*(longlong **)pDVar2,*(undefined4 *)(param_1 + 0x8f0));
  if (iVar9 != 0) {
    pbVar18 = (basicString<char> *)royale::getErrorString((CameraStatus)local_228);
    pcVar12 = (char *)FUN_180043dd0(&local_138);
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (local_338,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x15f,2);
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    pbVar14 = std::operator<<<std::char_traits<char>_>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
                         "Cant set exposure. ERROR: ");
    royale::operator<<<char>((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pbVar18);
    google::LogMessage::~LogMessage(local_338);
    if (0xf < uStack_120) {
      uVar7 = CONCAT71(uStack_137,local_138);
      uVar22 = uVar7;
      if ((0xfff < uStack_120 + 1) &&
         ((((local_138 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22)) ||
          (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_180002658(uVar22);
    }
    local_128 = _DAT_1800a15a0;
    uStack_120 = _UNK_1800a15a8;
    local_138 = 0;
    royale::basicString<char>::~basicString<char>(local_228);
    return;
  }
  if (param_1[0xd18] == (DeviceStreamBlock)0x0) {
    return;
  }
  local_1c8 = 0;
  local_1c0 = 0xf;
  local_1d8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
  local_1e8 = _DAT_1800a15a0;
  uStack_1e0 = _UNK_1800a15a8;
  local_1f8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
  pbVar15 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(param_1 + 0xdb8);
  fou::os::BreakFileNameAndExtension(pbVar15,&local_1d8,&local_1f8);
  pbVar24 = &local_1f8;
  if (0xf < uStack_1e0) {
    pbVar24 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              CONCAT71(uStack_1f7,local_1f8);
  }
  if (local_1e8 == 4) {
    lVar20 = 0;
    do {
      lVar21 = lVar20 + 1;
      if (pbVar24[lVar20] !=
          *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           (&DAT_18009f718 + lVar20)) {
        uVar10 = -(uint)((byte)pbVar24[lVar20] <
                        (byte)*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(&DAT_18009f718 + lVar20)) | 1;
        goto LAB_18004672d;
      }
      lVar20 = lVar21;
    } while (lVar21 != 4);
    uVar10 = 0;
LAB_18004672d:
    if (uVar10 == 0) goto LAB_1800468de;
  }
  if (0 < *(int *)FLAGS_v_exref) {
    pcVar12 = (char *)FUN_180043dd0(local_d8);
    local_398 = uVar25 | 4;
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (local_328,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x16c);
    uVar25 = uVar25 | 0xc;
    local_398 = uVar25;
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    std::operator<<<std::char_traits<char>_>
              ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
               "royale_recording_filename_ extension should be .rrf");
  }
  if ((uVar25 & 8) != 0) {
    uVar25 = uVar25 & 0xfffffff7;
    google::LogMessage::~LogMessage(local_328);
  }
  if (((uVar25 & 4) != 0) && (uVar25 = uVar25 & 0xfffffffb, 0xf < local_c0)) {
    uVar22 = local_d8[0];
    if ((0xfff < local_c0 + 1) &&
       ((((local_d8[0] & 0x1f) != 0 ||
         (uVar22 = *(ulonglong *)(local_d8[0] - 8), local_d8[0] <= uVar22)) ||
        (0x1f < (local_d8[0] - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  local_1a8 = _DAT_1800a15a0;
  uStack_1a0 = _UNK_1800a15a8;
  local_1b8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  local_398 = uVar25 | 0x10;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::reserve
            (&local_1b8,local_1c8 + 4);
  pbVar24 = &local_1d8;
  if (0xf < local_1c0) {
    pbVar24 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              CONCAT71(uStack_1d7,local_1d8);
  }
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::append
            (&local_1b8,(char *)pbVar24,local_1c8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::append(&local_1b8,".rrf",4);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::operator=
            (pbVar15,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )&local_1b8);
  if (0xf < uStack_1a0) {
    uVar7 = CONCAT71(uStack_1b7,local_1b8);
    uVar22 = uVar7;
    if ((0xfff < uStack_1a0 + 1) &&
       (((((byte)local_1b8 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22)) ||
        (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
LAB_1800468de:
  pAVar19 = coco::ApplicationManager::Get();
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>
            (&local_198,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (pAVar19 + 0x180));
  FUN_180040120(&local_178,pbVar15,&local_198);
  if (0xf < uStack_180) {
    uVar7 = CONCAT71(uStack_197,local_198);
    uVar22 = uVar7;
    if ((0xfff < uStack_180 + 1) &&
       (((((byte)local_198 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22)) ||
        (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  local_188 = _DAT_1800a15a0;
  uStack_180 = _UNK_1800a15a8;
  local_198 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  royale::basicString<char>::basicString<char>(local_2b8,&local_178);
  local_3a8 = 0;
  (**(code **)(**(longlong **)pDVar2 + 0x168))(*(longlong **)pDVar2,local_2b8,0,0);
  royale::basicString<char>::~basicString<char>(local_2b8);
  if (0xf < uStack_160) {
    uVar7 = CONCAT71(uStack_177,local_178);
    uVar22 = uVar7;
    if ((0xfff < uStack_160 + 1) &&
       (((((byte)local_178 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22)) ||
        (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  local_168 = _DAT_1800a15a0;
  uStack_160 = _UNK_1800a15a8;
  local_178 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  if (0xf < uStack_1e0) {
    uVar7 = CONCAT71(uStack_1f7,local_1f8);
    uVar22 = uVar7;
    if ((0xfff < uStack_1e0 + 1) &&
       (((((byte)local_1f8 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22)) ||
        (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  local_1e8 = _DAT_1800a15a0;
  uStack_1e0 = _UNK_1800a15a8;
  local_1f8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
  if (0xf < local_1c0) {
    uVar7 = CONCAT71(uStack_1d7,local_1d8);
    uVar22 = uVar7;
    if ((0xfff < local_1c0 + 1) &&
       (((((byte)local_1d8 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22)) ||
        (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  return;
}


/* ==================== ~_Func_class<void,royale::DepthData_const*___ptr64> @ 180001032  (5 bytes) ==================== */

/* public: __cdecl std::_Func_class<void,struct royale::DepthData const *
   __ptr64>::~_Func_class<void,struct royale::DepthData const * __ptr64>(void) __ptr64 */

void __thiscall
std::_Func_class<void,royale::DepthData_const*___ptr64>::
~_Func_class<void,royale::DepthData_const*___ptr64>
          (_Func_class<void,royale::DepthData_const*___ptr64> *this)

{
  _Func_class<void,royale::DepthData_const*___ptr64> *p_Var1;
  
                    /* 0x1032  2151  ??1?$_Func_class@XPEBUDepthData@royale@@@std@@QEAA@XZ */
  p_Var1 = *(_Func_class<void,royale::DepthData_const*___ptr64> **)(this + 0x38);
  if (p_Var1 != (_Func_class<void,royale::DepthData_const*___ptr64> *)0x0) {
    (**(code **)(*(longlong *)p_Var1 + 0x20))(p_Var1,p_Var1 != this);
    *(undefined8 *)(this + 0x38) = 0;
  }
  return;
}


/* ==================== CircularBuffer<std::shared_ptr<types::ImageFrame>_> @ 18000104b  (5 bytes) ==================== */

/* public: __cdecl coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame>
   >::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >(unsigned __int64) __ptr64 */

CircularBuffer<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>::
CircularBuffer<std::shared_ptr<types::ImageFrame>_>
          (CircularBuffer<std::shared_ptr<types::ImageFrame>_> *this,__uint64 param_1)

{
  CircularBuffer<std::shared_ptr<types::ImageFrame>_> *pCVar1;
  undefined8 *puVar2;
  
                    /* 0x104b  1437
                       ??0?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@_K@Z
                        */
  *(undefined ***)this = BufferBase<std::shared_ptr<types::ImageFrame>_>::vftable;
  *(undefined4 *)(this + 8) = 0;
  this[0xc] = (CircularBuffer<std::shared_ptr<types::ImageFrame>_>)0x0;
  ConnectionStatisticsBuilder::ConnectionStatisticsBuilder
            ((ConnectionStatisticsBuilder *)(this + 0x10));
  *(undefined ***)this = vftable;
  pCVar1 = this + 0x118;
  *(undefined8 *)pCVar1 = 0;
  *(undefined8 *)(this + 0x120) = 0;
  *(undefined8 *)(this + 0x128) = 0;
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined8 *)(this + 0x138) = 0;
  puVar2 = (undefined8 *)thunk_FUN_180084ee4(0x10);
  if (puVar2 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
    _invalid_parameter_noinfo_noreturn();
  }
  *(undefined8 **)pCVar1 = puVar2;
  *puVar2 = 0;
  puVar2[1] = 0;
  **(undefined8 **)pCVar1 = pCVar1;
  *(__uint64 *)(this + 0x140) = param_1;
  *(__uint64 *)(this + 0x38) = param_1;
  *(undefined8 *)(this + 0x98) = 0x7ff0000000000000;
  *(undefined8 *)(this + 0xd8) = 0x7ff0000000000000;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  ConnectionStatisticsBuilder::ResetProducerStats((ConnectionStatisticsBuilder *)(this + 0x10));
  *(undefined8 *)(this + 0x80) = 0x7ff0000000000000;
  return this;
}


/* ==================== function<void___cdecl(royale::DepthData_const*___ptr64)> @ 18000112c  (5 bytes) ==================== */

/* public: __cdecl std::function<void __cdecl(struct royale::DepthData const *
   __ptr64)>::function<void __cdecl(struct royale::DepthData const * __ptr64)>(void) __ptr64 */

function<void___cdecl(royale::DepthData_const*___ptr64)> * __thiscall
std::function<void___cdecl(royale::DepthData_const*___ptr64)>::
function<void___cdecl(royale::DepthData_const*___ptr64)>
          (function<void___cdecl(royale::DepthData_const*___ptr64)> *this)

{
                    /* 0x112c  1789  ??0?$function@$$A6AXPEBUDepthData@royale@@@Z@std@@QEAA@XZ */
  *(undefined8 *)(this + 0x38) = 0;
  return this;
}


/* ==================== make_unique<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,void> @ 1800011ae  (5 bytes) ==================== */

/* class std::unique_ptr<class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> > > > __cdecl std::make_unique<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame>
   >,void>(void) */

void __cdecl
std::make_unique<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,void>
          (void)

{
  undefined8 *puVar1;
  undefined8 *in_RCX;
  
                    /* 0x11ae  1338
                       ??$make_unique@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$$VX@std@@YA?AV?$unique_ptr@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@0@XZ
                        */
  puVar1 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar1 == (undefined8 *)0x0) {
    *in_RCX = 0;
    return;
  }
  puVar1[1] = 0;
  *(undefined1 *)(puVar1 + 1) = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  *puVar1 = coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar1[5] = 0;
  *in_RCX = puVar1;
  return;
}


/* ==================== operator=<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>,void> @ 1800011cc  (5 bytes) ==================== */

/* public: class std::unique_ptr<class coco::ConnectionManager,struct std::default_delete<class
   coco::ConnectionManager> > & __ptr64 __cdecl std::unique_ptr<class coco::ConnectionManager,struct
   std::default_delete<class coco::ConnectionManager> >::operator=<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> > >,void>(class std::unique_ptr<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> > > > && __ptr64) __ptr64 */

unique_ptr<class_coco::ConnectionManager,struct_std::default_delete<class_coco::ConnectionManager>_>
* __thiscall
std::unique_ptr<coco::ConnectionManager,std::default_delete<coco::ConnectionManager>_>::
operator=<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>,void>
          (unique_ptr<coco::ConnectionManager,std::default_delete<coco::ConnectionManager>_> *this,
          unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
          *param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
                    /* 0x11cc  339
                       ??$?4V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@X@?$unique_ptr@VConnectionManager@coco@@U?$default_delete@VConnectionManager@coco@@@std@@@std@@QEAAAEAV01@$$QEAV?$unique_ptr@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@1@@Z
                        */
  uVar1 = *(undefined8 *)param_1;
  *(undefined8 *)param_1 = 0;
  puVar2 = *(undefined8 **)this;
  *(undefined8 *)this = uVar1;
  if (puVar2 != (undefined8 *)0x0) {
    (**(code **)*puVar2)(puVar2,1);
  }
  return (unique_ptr<class_coco::ConnectionManager,struct_std::default_delete<class_coco::ConnectionManager>_>
          *)this;
}


/* ==================== ~ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_> @ 180001221  (5 bytes) ==================== */

/* public: virtual __cdecl coco::ConnectionManagerInput<class std::shared_ptr<struct
   types::ImageFrame> >::~ConnectionManagerInput<class std::shared_ptr<struct types::ImageFrame>
   >(void) __ptr64 */

void __thiscall
coco::ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_>::
~ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x1221  2040
                       ??1?$ConnectionManagerInput@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ
                        */
  std::
  vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
  ::_Tidy((vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
           *)(this + 0x10));
  return;
}


/* ==================== _Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_> @ 18000123f  (5 bytes) ==================== */

/* public: __cdecl std::_Tree_iterator<class std::_Tree_val<struct std::_Tree_simple_types<struct
   std::pair<unsigned int const ,struct sdc::TofConfig> > > >::_Tree_iterator<class
   std::_Tree_val<struct std::_Tree_simple_types<struct std::pair<unsigned int const ,struct
   sdc::TofConfig> > > >(struct std::_Tree_node<struct std::pair<unsigned int const ,struct
   sdc::TofConfig>,void * __ptr64> * __ptr64,class std::_Tree_val<struct
   std::_Tree_simple_types<struct std::pair<unsigned int const ,struct sdc::TofConfig> > > const *
   __ptr64) __ptr64 */

_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_>
* __thiscall
std::
_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_>
::
_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_>
          (_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_>
           *this,_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> *param_1,
          _Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>
          *param_2)

{
                    /* 0x123f  1700
                       ??0?$_Tree_iterator@V?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBIUTofConfig@sdc@@@std@@@std@@@std@@@std@@QEAA@PEAU?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@1@PEBV?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBIUTofConfig@sdc@@@std@@@std@@@1@@Z
                        */
  *(_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> **)this = param_1;
  return this;
}


/* ==================== forward<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180001276  (5 bytes) ==================== */

/* class coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64
   __cdecl std::forward<class coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64>(class coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64) */

BufferBase<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::forward<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_> **param_1)

{
                    /* 0x1276  1043
                       ??$forward@AEAPEAV?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YAAEAPEAV?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (BufferBase<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== _Unique_ptr_base<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_><coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64> @ 180001325  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class coco::Data<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::Data<class std::shared_ptr<struct
   types::ImageFrame> > > >::_Unique_ptr_base<class coco::Data<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::Data<class std::shared_ptr<struct
   types::ImageFrame> > > ><class coco::Data<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64>(class coco::Data<class std::shared_ptr<struct types::ImageFrame> > * __ptr64) __ptr64 */

_Unique_ptr_base<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Unique_ptr_base<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Unique_ptr_base<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_><coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64>
          (_Unique_ptr_base<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,Data<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x1325  182
                       ??$?0PEAV?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Unique_ptr_base@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(Data<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== _Destroy_range1<std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_> @ 18000133e  (5 bytes) ==================== */

/* void __cdecl std::_Destroy_range1<class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> * __ptr64> >(class std::shared_ptr<struct types::ImageFrame> * __ptr64 *
   __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> * __ptr64> & __ptr64,struct
   std::integral_constant<bool,1>) */

void __cdecl
std::_Destroy_range1<std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_>(void)

{
                    /* 0x133e  471
                       ??$_Destroy_range1@V?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@YAXPEAPEAV?$shared_ptr@UImageFrame@types@@@0@0AEAV?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@0@U?$integral_constant@_N$00@0@@Z
                        */
  return;
}


/* ==================== move<royale::Variant&___ptr64> @ 1800013a2  (5 bytes) ==================== */

/* class royale::Variant && __ptr64 __cdecl std::move<class royale::Variant & __ptr64>(class
   royale::Variant & __ptr64) */

Variant * __cdecl std::move<royale::Variant&___ptr64>(Variant *param_1)

{
                    /* 0x13a2  1402
                       ??$move@AEAVVariant@royale@@@std@@YA$$QEAVVariant@royale@@AEAV12@@Z */
  return param_1;
}


/* ==================== ~pair<royale::ProcessingFlag,royale::Variant> @ 1800013ed  (5 bytes) ==================== */

/* public: __cdecl std::pair<enum royale::ProcessingFlag,class royale::Variant>::~pair<enum
   royale::ProcessingFlag,class royale::Variant>(void) __ptr64 */

void __thiscall
std::pair<royale::ProcessingFlag,royale::Variant>::~pair<royale::ProcessingFlag,royale::Variant>
          (pair<royale::ProcessingFlag,royale::Variant> *this)

{
                    /* 0x13ed  2298  ??1?$pair@W4ProcessingFlag@royale@@VVariant@2@@std@@QEAA@XZ */
  royale::Variant::~Variant((Variant *)(this + 4));
  return;
}


/* ==================== _Zero_range<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64> @ 180001406  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 __cdecl
   std::_Zero_range<class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64>(class
   std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,class std::shared_ptr<struct
   types::ImageFrame> * __ptr64 * __ptr64) */

shared_ptr<types::ImageFrame> ** __cdecl
std::_Zero_range<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64>
          (shared_ptr<struct_types::ImageFrame> **param_1,
          shared_ptr<struct_types::ImageFrame> **param_2)

{
                    /* 0x1406  774
                       ??$_Zero_range@PEAPEAV?$shared_ptr@UImageFrame@types@@@std@@@std@@YAPEAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAPEAV10@0@Z
                        */
  memset(param_1,0,(longlong)param_2 - (longlong)param_1);
  return (shared_ptr<types::ImageFrame> **)param_2;
}


/* ==================== _Destroy_range<std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_> @ 180001415  (5 bytes) ==================== */

/* void __cdecl std::_Destroy_range<class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> * __ptr64> >(class std::shared_ptr<struct types::ImageFrame> * __ptr64 *
   __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> * __ptr64> & __ptr64) */

void __cdecl
std::_Destroy_range<std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_>
          (shared_ptr<types::ImageFrame> **param_1,shared_ptr<types::ImageFrame> **param_2,
          allocator<std::shared_ptr<types::ImageFrame>*___ptr64> *param_3)

{
                    /* 0x1415  492
                       ??$_Destroy_range@V?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@YAXPEAPEAV?$shared_ptr@UImageFrame@types@@@0@0AEAV?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@0@@Z
                        */
  return;
}


/* ==================== construct<std::shared_ptr<types::ImageFrame>,std::shared_ptr<struct_types::ImageFrame>_> @ 1800014bf  (5 bytes) ==================== */

/* public: static void __cdecl std::_Default_allocator_traits<class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> > >::construct<class std::shared_ptr<struct
   types::ImageFrame>,class std::shared_ptr<struct types::ImageFrame> >(class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> > & __ptr64,class std::shared_ptr<struct
   types::ImageFrame> * __ptr64 const,class std::shared_ptr<struct types::ImageFrame> && __ptr64) */

void __cdecl
std::_Default_allocator_traits<std::allocator<std::shared_ptr<types::ImageFrame>_>_>::
construct<std::shared_ptr<types::ImageFrame>,std::shared_ptr<struct_types::ImageFrame>_>
          (allocator<std::shared_ptr<types::ImageFrame>_> *param_1,
          shared_ptr<types::ImageFrame> *param_2,shared_ptr<struct_types::ImageFrame> *param_3)

{
                    /* 0x14bf  932
                       ??$construct@V?$shared_ptr@UImageFrame@types@@@std@@V12@@?$_Default_allocator_traits@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@SAXAEAV?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@1@QEAV?$shared_ptr@UImageFrame@types@@@1@$$QEAV31@@Z
                        */
  *(undefined8 *)param_2 = *(undefined8 *)param_3;
  *(undefined8 *)(param_2 + 8) = *(undefined8 *)(param_3 + 8);
  *(undefined8 *)param_3 = 0;
  *(undefined8 *)(param_3 + 8) = 0;
  return;
}


/* ==================== get<0,royale::DepthData_const*___ptr64&&___ptr64> @ 180001578  (5 bytes) ==================== */

/* struct royale::DepthData const * __ptr64 && __ptr64 __cdecl std::get<0,struct royale::DepthData
   const * __ptr64 && __ptr64>(class std::tuple<struct royale::DepthData const * __ptr64 && __ptr64>
   && __ptr64) */

DepthData ** __cdecl
std::get<0,royale::DepthData_const*___ptr64&&___ptr64>
          (tuple<royale::DepthData_const*___ptr64&&___ptr64> *param_1)

{
                    /* 0x1578  1261
                       ??$get@$0A@$$QEAPEBUDepthData@royale@@@std@@YA$$QEAPEBUDepthData@royale@@$$QEAV?$tuple@$$QEAPEBUDepthData@royale@@@0@@Z
                        */
  return *(DepthData ***)param_1;
}


/* ==================== forward<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180001587  (5 bytes) ==================== */

/* class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64 __cdecl std::forward<class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64>(class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > * __ptr64
   & __ptr64) */

ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::
forward<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (ConnectionManagerOutputDefault<class_std::shared_ptr<struct_types::ImageFrame>_>
           **param_1)

{
                    /* 0x1587  1060
                       ??$forward@AEAPEAV?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YAAEAPEAV?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== _Compressed_pair<std::default_delete<royale::ICameraDevice>,royale::ICameraDevice*___ptr64,1><royale::ICameraDevice*___ptr64&___ptr64> @ 18000159b  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class
   royale::ICameraDevice>,class royale::ICameraDevice * __ptr64,1>::_Compressed_pair<struct
   std::default_delete<class royale::ICameraDevice>,class royale::ICameraDevice * __ptr64,1><class
   royale::ICameraDevice * __ptr64 & __ptr64>(struct std::_Zero_then_variadic_args_t,class
   royale::ICameraDevice * __ptr64 & __ptr64) __ptr64 */

_Compressed_pair<std::default_delete<royale::ICameraDevice>,royale::ICameraDevice*___ptr64,1> *
__thiscall
std::_Compressed_pair<std::default_delete<royale::ICameraDevice>,royale::ICameraDevice*___ptr64,1>::
_Compressed_pair<std::default_delete<royale::ICameraDevice>,royale::ICameraDevice*___ptr64,1><royale::ICameraDevice*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<royale::ICameraDevice>,royale::ICameraDevice*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x159b  75
                       ??$?0AEAPEAVICameraDevice@royale@@@?$_Compressed_pair@U?$default_delete@VICameraDevice@royale@@@std@@PEAVICameraDevice@royale@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAVICameraDevice@royale@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_> @ 1800015a5  (5 bytes) ==================== */

/* public: __cdecl coco::ConnectionManagerOutput<class std::shared_ptr<struct types::ImageFrame>
   >::ConnectionManagerOutput<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_>::
ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x15a5  1453
                       ??0?$ConnectionManagerOutput@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@XZ
                        */
  this[8] = (ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_>)0x0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined ***)this = vftable;
  return this;
}


/* ==================== _Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_>,1><> @ 180001672  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> >,class std::_Vector_val<struct std::_Simple_types<class
   std::shared_ptr<struct types::ImageFrame> > >,1>::_Compressed_pair<class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> >,class std::_Vector_val<struct
   std::_Simple_types<class std::shared_ptr<struct types::ImageFrame> > >,1><>(struct
   std::_Zero_then_variadic_args_t) __ptr64 */

_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_>,1>
* __thiscall
std::
_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_>,1>
::
_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_>,1><>
          (_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_>,1>
           *this)

{
                    /* 0x1672  9
                       ??$?0$$V@?$_Compressed_pair@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@std@@V?$_Vector_val@U?$_Simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@2@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@@Z
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  return this;
}


/* ==================== ~unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_> @ 180001690  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > >
   >::~unique_ptr<class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> > > >(void) __ptr64 */

void __thiscall
std::
unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
::
~unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x1690  2366
                       ??1?$unique_ptr@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000180031140. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== ~_Deque_const_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_> @ 1800016a4  (5 bytes) ==================== */

/* public: __cdecl std::_Deque_const_iterator<class std::_Deque_val<struct
   std::_Deque_simple_types<class std::shared_ptr<struct types::ImageFrame> > >
   >::~_Deque_const_iterator<class std::_Deque_val<struct std::_Deque_simple_types<class
   std::shared_ptr<struct types::ImageFrame> > > >(void) __ptr64 */

void __thiscall
std::
_Deque_const_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
::
~_Deque_const_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
          (_Deque_const_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
                    /* 0x16a4  2122
                       ??1?$_Deque_const_iterator@V?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@@std@@QEAA@XZ
                        */
  return;
}


/* ==================== ~_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_> @ 1800016d6  (5 bytes) ==================== */

/* public: __cdecl std::_Deque_val<struct std::_Deque_simple_types<class std::shared_ptr<struct
   types::ImageFrame> > >::~_Deque_val<struct std::_Deque_simple_types<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

void __thiscall
std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>::
~_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>
          (_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_> *this)

{
                    /* 0x16d6  2136
                       ??1?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@QEAA@XZ
                        */
  return;
}


/* ==================== Imu1FrameGrabber @ 180001762  (5 bytes) ==================== */

/* private: void __cdecl meta::blocks::DeviceStreamBlock::Imu1FrameGrabber(class
   std::shared_ptr<struct sdc::RawImuData> const & __ptr64) __ptr64 */

void __thiscall
meta::blocks::DeviceStreamBlock::Imu1FrameGrabber
          (DeviceStreamBlock *this,shared_ptr<sdc::RawImuData> *param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  MatrixStamped<short,3,1> *pMStack_60;
  longlong *plStack_58;
  MatrixStamped<short,3,1> *pMStack_50;
  longlong *plStack_48;
  
                    /* 0x1762  3106
                       ?Imu1FrameGrabber@DeviceStreamBlock@blocks@meta@@AEAAXAEBV?$shared_ptr@URawImuData@sdc@@@std@@@Z
                        */
  plStack_58 = (longlong *)thunk_FUN_180084ee4(0x70);
  if (plStack_58 == (longlong *)0x0) {
    plStack_58 = (longlong *)0x0;
  }
  else {
    *(undefined4 *)(plStack_58 + 1) = 1;
    *(undefined4 *)((longlong)plStack_58 + 0xc) = 1;
    *plStack_58 = (longlong)std::_Ref_count_obj<types::MatrixStamped<short,3,1>_>::vftable;
    types::Header::Header((Header *)(plStack_58 + 2));
    *(undefined4 *)(plStack_58 + 0xd) = 0;
    *(undefined2 *)((longlong)plStack_58 + 0x6c) = 0;
  }
  pMStack_60 = (MatrixStamped<short,3,1> *)(plStack_58 + 2);
  plStack_48 = (longlong *)thunk_FUN_180084ee4(0x70);
  if (plStack_48 == (longlong *)0x0) {
    plStack_48 = (longlong *)0x0;
  }
  else {
    *(undefined4 *)(plStack_48 + 1) = 1;
    *(undefined4 *)((longlong)plStack_48 + 0xc) = 1;
    *plStack_48 = (longlong)std::_Ref_count_obj<types::MatrixStamped<short,3,1>_>::vftable;
    types::Header::Header((Header *)(plStack_48 + 2));
    *(undefined4 *)(plStack_48 + 0xd) = 0;
    *(undefined2 *)((longlong)plStack_48 + 0x6c) = 0;
  }
  pMStack_50 = (MatrixStamped<short,3,1> *)(plStack_48 + 2);
  CreateImuFrame(this,param_1,pMStack_60,pMStack_50);
  if (0.0 < *(double *)(pMStack_60 + 8)) {
    (**(code **)(**(longlong **)(this + 0x6c8) + 8))(*(longlong **)(this + 0x6c8),&pMStack_60);
  }
  if (0.0 < *(double *)(pMStack_50 + 8)) {
    (**(code **)(**(longlong **)(this + 0x730) + 8))(*(longlong **)(this + 0x730),&pMStack_50);
  }
  plVar5 = plStack_48;
  if (plStack_48 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_48 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_48)(plStack_48);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  plVar5 = plStack_58;
  if (plStack_58 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_58 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_58)(plStack_58);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}


/* ==================== BufferBase<std::shared_ptr<types::ImageFrame>_> @ 180001820  (5 bytes) ==================== */

/* public: __cdecl coco::BufferBase<class std::shared_ptr<struct types::ImageFrame>
   >::BufferBase<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

BufferBase<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::BufferBase<std::shared_ptr<types::ImageFrame>_>::
BufferBase<std::shared_ptr<types::ImageFrame>_>
          (BufferBase<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x1820  1431
                       ??0?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@XZ */
  *(undefined4 *)(this + 8) = 0;
  *(undefined ***)this = vftable;
  this[0xc] = (BufferBase<std::shared_ptr<types::ImageFrame>_>)0x0;
  ConnectionStatisticsBuilder::ConnectionStatisticsBuilder
            ((ConnectionStatisticsBuilder *)(this + 0x10));
  return this;
}


/* ==================== _Unique_ptr_base<RoyaleDataListener,std::default_delete<RoyaleDataListener>_><RoyaleDataListener*___ptr64> @ 180001861  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class RoyaleDataListener,struct std::default_delete<class
   RoyaleDataListener> >::_Unique_ptr_base<class RoyaleDataListener,struct std::default_delete<class
   RoyaleDataListener> ><class RoyaleDataListener * __ptr64>(class RoyaleDataListener * __ptr64)
   __ptr64 */

_Unique_ptr_base<RoyaleDataListener,std::default_delete<RoyaleDataListener>_> * __thiscall
std::_Unique_ptr_base<RoyaleDataListener,std::default_delete<RoyaleDataListener>_>::
_Unique_ptr_base<RoyaleDataListener,std::default_delete<RoyaleDataListener>_><RoyaleDataListener*___ptr64>
          (_Unique_ptr_base<RoyaleDataListener,std::default_delete<RoyaleDataListener>_> *this,
          RoyaleDataListener *param_1)

{
                    /* 0x1861  194
                       ??$?0PEAVRoyaleDataListener@@@?$_Unique_ptr_base@VRoyaleDataListener@@U?$default_delete@VRoyaleDataListener@@@std@@@std@@QEAA@PEAVRoyaleDataListener@@@Z
                        */
  *(RoyaleDataListener **)this = param_1;
  return this;
}


/* ==================== ~ImageFrame @ 180001875  (5 bytes) ==================== */

/* public: __cdecl types::ImageFrame::~ImageFrame(void) __ptr64 */

void __thiscall types::ImageFrame::~ImageFrame(ImageFrame *this)

{
                    /* 0x1875  2413  ??1ImageFrame@types@@QEAA@XZ */
  cv::Mat::release((Mat *)(this + 0x58));
  if (*(ImageFrame **)(this + 0xa0) != this + 0xa8) {
    cv::fastFree(*(ImageFrame **)(this + 0xa0));
  }
  std::
  vector<std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>_>,std::allocator<std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>_>_>_>
  ::_Tidy((vector<std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>_>,std::allocator<std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>_>_>_>
           *)(this + 0x28));
  std::
  list<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
  ::
  ~list<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
            ((list<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
              *)(this + 0x18));
  return;
}


/* ==================== _Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_><coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64,coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64,coco::ConnectionPolicy&___ptr64> @ 18000192e  (5 bytes) ==================== */

/* public: __cdecl std::_Ref_count_obj<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >::_Ref_count_obj<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > ><class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64,class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,struct coco::ConnectionPolicy & __ptr64>(class coco::InputPort<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64,class coco::OutputPort<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 && __ptr64,struct coco::ConnectionPolicy &
   __ptr64) __ptr64 */

_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_><coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64,coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64,coco::ConnectionPolicy&___ptr64>
          (_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *this,
          InputPort<std::shared_ptr<types::ImageFrame>_> **param_1,
          OutputPort<std::shared_ptr<types::ImageFrame>_> **param_2,ConnectionPolicy *param_3)

{
  OutputPort<std::shared_ptr<types::ImageFrame>_> *pOVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
                    /* 0x192e  69
                       ??$?0AEAPEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@PEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@1@AEAUConnectionPolicy@1@@?$_Ref_count_obj@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@AEAPEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$$QEAPEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@3@AEAUConnectionPolicy@3@@Z
                        */
  *(undefined4 *)(this + 8) = 1;
  *(undefined4 *)(this + 0xc) = 1;
  *(undefined ***)this = vftable;
  pOVar1 = *param_2;
  uVar2 = *(undefined4 *)param_3;
  uVar3 = *(undefined4 *)(param_3 + 4);
  uVar4 = *(undefined4 *)(param_3 + 8);
  uVar5 = *(undefined4 *)(param_3 + 0xc);
  *(InputPort<std::shared_ptr<types::ImageFrame>_> **)(this + 0x18) = *param_1;
  *(OutputPort<std::shared_ptr<types::ImageFrame>_> **)(this + 0x20) = pOVar1;
  *(undefined4 *)(this + 0x28) = uVar2;
  *(undefined4 *)(this + 0x2c) = uVar3;
  *(undefined4 *)(this + 0x30) = uVar4;
  *(undefined4 *)(this + 0x34) = uVar5;
  *(undefined8 *)(this + 0x38) = 0;
  this[0x40] = (_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>)0x0;
  *(undefined ***)(this + 0x10) =
       coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::vftable;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
  _Mtx_init_in_situ(this + 0x58,2,param_2,param_3,0xfffffffffffffffe);
  _Cnd_init_in_situ(this + 0xa8);
  coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::CreateConnection
            ((ConnectionTyped<std::shared_ptr<types::ImageFrame>_> *)(this + 0x10));
  return this;
}


/* ==================== invoke<void_(__cdecl_meta::blocks::DeviceStreamBlock::*&___ptr64)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64&___ptr64,royale::DepthData_const*___ptr64> @ 180001a37  (5 bytes) ==================== */

/* void __cdecl std::invoke<void (__cdecl meta::blocks::DeviceStreamBlock::*& __ptr64)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64 &
   __ptr64,struct royale::DepthData const * __ptr64>(void (__cdecl
   meta::blocks::DeviceStreamBlock::*& __ptr64)(struct royale::DepthData const * __ptr64)
   __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64 & __ptr64,struct royale::DepthData const
   * __ptr64 && __ptr64) */

void __cdecl
std::
invoke<void_(__cdecl_meta::blocks::DeviceStreamBlock::*&___ptr64)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64&___ptr64,royale::DepthData_const*___ptr64>
          (_func_void_DepthData_ptr **param_1,DeviceStreamBlock **param_2,DepthData **param_3)

{
                    /* 0x1a37  1278
                       ??$invoke@AEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZAEAPEAV123@PEBU45@@std@@YAXAEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZAEAPEAV123@$$QEAPEBU45@@Z
                        */
                    /* WARNING: Could not recover jumptable at 0x000180020ccc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**param_1)((DepthData *)*param_2);
  return;
}


/* ==================== ~unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_> @ 180001aa5  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::CircularBuffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> > > >::~unique_ptr<class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> > > >(void) __ptr64 */

void __thiscall
std::
unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
::
~unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x1aa5  2349
                       ??1?$unique_ptr@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000180031000. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_> @ 180001ab4  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > >
   >::unique_ptr<class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> > > >(class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64) __ptr64 */

unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
::
unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x1ab4  1895
                       ??0?$unique_ptr@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== _Rechecked<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64> @ 180001ae6  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 & __ptr64 __cdecl std::_Rechecked<class
   std::shared_ptr<struct types::ImageFrame> * __ptr64,class std::shared_ptr<struct
   types::ImageFrame> * __ptr64>(class std::shared_ptr<struct types::ImageFrame> * __ptr64 &
   __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64) */

shared_ptr<types::ImageFrame> ** __cdecl
std::
_Rechecked<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64>
          (shared_ptr<struct_types::ImageFrame> **param_1,
          shared_ptr<struct_types::ImageFrame> *param_2)

{
                    /* 0x1ae6  603
                       ??$_Rechecked@PEAV?$shared_ptr@UImageFrame@types@@@std@@PEAV12@@std@@YAAEAPEAV?$shared_ptr@UImageFrame@types@@@0@AEAPEAV10@PEAV10@@Z
                        */
  *param_1 = param_2;
  return (shared_ptr<types::ImageFrame> **)param_1;
}


/* ==================== _Func_class<void,royale::DepthData_const*___ptr64> @ 180001bbd  (5 bytes) ==================== */

/* public: __cdecl std::_Func_class<void,struct royale::DepthData const *
   __ptr64>::_Func_class<void,struct royale::DepthData const * __ptr64>(void) __ptr64 */

_Func_class<void,royale::DepthData_const*___ptr64> * __thiscall
std::_Func_class<void,royale::DepthData_const*___ptr64>::
_Func_class<void,royale::DepthData_const*___ptr64>
          (_Func_class<void,royale::DepthData_const*___ptr64> *this)

{
                    /* 0x1bbd  1621  ??0?$_Func_class@XPEBUDepthData@royale@@@std@@QEAA@XZ */
  *(undefined8 *)(this + 0x38) = 0;
  return this;
}


/* ==================== allocator<std::_Container_proxy><std::shared_ptr<types::ImageFrame>_> @ 180001c1c  (5 bytes) ==================== */

/* public: __cdecl std::allocator<struct std::_Container_proxy>::allocator<struct
   std::_Container_proxy><class std::shared_ptr<struct types::ImageFrame> >(class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> > const & __ptr64) __ptr64 */

allocator<std::_Container_proxy> * __thiscall
std::allocator<std::_Container_proxy>::
allocator<std::_Container_proxy><std::shared_ptr<types::ImageFrame>_>
          (allocator<std::_Container_proxy> *this,
          allocator<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x1c1c  300
                       ??$?0V?$shared_ptr@UImageFrame@types@@@std@@@?$allocator@U_Container_proxy@std@@@std@@QEAA@AEBV?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@1@@Z
                        */
  return this;
}


/* ==================== move<royale::ProcessingFlag&___ptr64> @ 180001c44  (5 bytes) ==================== */

/* enum royale::ProcessingFlag && __ptr64 __cdecl std::move<enum royale::ProcessingFlag &
   __ptr64>(enum royale::ProcessingFlag & __ptr64) */

ProcessingFlag * __cdecl std::move<royale::ProcessingFlag&___ptr64>(ProcessingFlag *param_1)

{
                    /* 0x1c44  1403
                       ??$move@AEAW4ProcessingFlag@royale@@@std@@YA$$QEAW4ProcessingFlag@royale@@AEAW412@@Z
                        */
  return param_1;
}


/* ==================== Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_> @ 180001c7b  (5 bytes) ==================== */

/* public: __cdecl royale::Vector<class royale::Pair<enum royale::ProcessingFlag,class
   royale::Variant> >::Vector<class royale::Pair<enum royale::ProcessingFlag,class royale::Variant>
   >(void) __ptr64 */

Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_> * __thiscall
royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>
          (Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_> *this)

{
                    /* 0x1c7b  1518
                       ??0?$Vector@V?$Pair@W4ProcessingFlag@royale@@VVariant@2@@royale@@@royale@@QEAA@XZ
                        */
  *(undefined ***)this = vftable;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x28) = 2;
  return this;
}


/* ==================== forward<std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_> @ 180001ca3  (5 bytes) ==================== */

/* struct std::default_delete<class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> > > && __ptr64 __cdecl std::forward<struct
   std::default_delete<class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> > > >(struct std::default_delete<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > > &
   __ptr64) */

default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_> * __cdecl
std::
forward<std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
          (default_delete<class_coco::ConnectionManagerOutputDefault<class_std::shared_ptr<struct_types::ImageFrame>_>_>
           *param_1)

{
                    /* 0x1ca3  1202
                       ??$forward@U?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@YA$$QEAU?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@0@AEAU10@@Z
                        */
  return (default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>
          *)param_1;
}


/* ==================== default_delete<coco::ConnectionManager><coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,void> @ 180001d52  (5 bytes) ==================== */

/* public: __cdecl std::default_delete<class coco::ConnectionManager>::default_delete<class
   coco::ConnectionManager><class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,void>(struct std::default_delete<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > > const &
   __ptr64) __ptr64 */

default_delete<coco::ConnectionManager> * __thiscall
std::default_delete<coco::ConnectionManager>::
default_delete<coco::ConnectionManager><coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,void>
          (default_delete<coco::ConnectionManager> *this,
          default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>
          *param_1)

{
                    /* 0x1d52  234
                       ??$?0V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@X@?$default_delete@VConnectionManager@coco@@@std@@QEAA@AEBU?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@1@@Z
                        */
  return this;
}


/* ==================== _Call<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64,royale::DepthData_const*___ptr64> @ 180001e74  (5 bytes) ==================== */

/* public: static void __cdecl std::_Invoker_functor::_Call<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> & __ptr64,struct royale::DepthData const * __ptr64>(class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> & __ptr64,struct royale::DepthData const * __ptr64 && __ptr64) */

void __cdecl
std::_Invoker_functor::
_Call<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64,royale::DepthData_const*___ptr64>
          (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
           *param_1,DepthData **param_2)

{
                    /* 0x1e74  430
                       ??$_Call@AEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@PEBUDepthData@royale@@@_Invoker_functor@std@@SAXAEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@1@$$QEAPEBUDepthData@royale@@@Z
                        */
                    /* WARNING: Could not recover jumptable at 0x00018001a77a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)param_1)(*(undefined8 *)(param_1 + 0x10),*param_2);
  return;
}


/* ==================== Pair<royale::ProcessingFlag,royale::Variant> @ 180001ef1  (5 bytes) ==================== */

/* public: __cdecl royale::Pair<enum royale::ProcessingFlag,class royale::Variant>::Pair<enum
   royale::ProcessingFlag,class royale::Variant>(enum royale::ProcessingFlag && __ptr64,class
   royale::Variant && __ptr64) __ptr64 */

Pair<royale::ProcessingFlag,royale::Variant> * __thiscall
royale::Pair<royale::ProcessingFlag,royale::Variant>::Pair<royale::ProcessingFlag,royale::Variant>
          (Pair<royale::ProcessingFlag,royale::Variant> *this,ProcessingFlag *param_1,
          Variant *param_2)

{
  undefined8 uVar1;
  
                    /* 0x1ef1  1513
                       ??0?$Pair@W4ProcessingFlag@royale@@VVariant@2@@royale@@QEAA@$$QEAW4ProcessingFlag@1@$$QEAVVariant@1@@Z
                        */
  *(undefined ***)this = vftable;
  *(ProcessingFlag *)(this + 8) = *param_1;
  uVar1 = *(undefined8 *)(param_2 + 8);
  *(undefined8 *)(this + 0xc) = *(undefined8 *)param_2;
  *(undefined8 *)(this + 0x14) = uVar1;
  *(undefined8 *)(this + 0x1c) = *(undefined8 *)(param_2 + 0x10);
  return this;
}


/* ==================== pair<royale::ProcessingFlag,royale::Variant><royale::ProcessingFlag,royale::Variant,void,0> @ 180001f1e  (5 bytes) ==================== */

/* public: __cdecl std::pair<enum royale::ProcessingFlag,class royale::Variant>::pair<enum
   royale::ProcessingFlag,class royale::Variant><enum royale::ProcessingFlag,class
   royale::Variant,void,0>(enum royale::ProcessingFlag && __ptr64,class royale::Variant && __ptr64)
   __ptr64 */

pair<royale::ProcessingFlag,royale::Variant> * __thiscall
std::pair<royale::ProcessingFlag,royale::Variant>::
pair<royale::ProcessingFlag,royale::Variant><royale::ProcessingFlag,royale::Variant,void,0>
          (pair<royale::ProcessingFlag,royale::Variant> *this,ProcessingFlag *param_1,
          Variant *param_2)

{
  undefined8 uVar1;
  
                    /* 0x1f1e  313
                       ??$?0W4ProcessingFlag@royale@@VVariant@1@X$0A@@?$pair@W4ProcessingFlag@royale@@VVariant@2@@std@@QEAA@$$QEAW4ProcessingFlag@royale@@$$QEAVVariant@3@@Z
                        */
  *(ProcessingFlag *)this = *param_1;
  uVar1 = *(undefined8 *)(param_2 + 8);
  *(undefined8 *)(this + 4) = *(undefined8 *)param_2;
  *(undefined8 *)(this + 0xc) = uVar1;
  *(undefined8 *)(this + 0x14) = *(undefined8 *)(param_2 + 0x10);
  return this;
}


/* ==================== royale_strlen<char> @ 180001f37  (5 bytes) ==================== */

/* unsigned __int64 __cdecl royale::royale_strlen<char>(char const * __ptr64) */

__uint64 __cdecl royale::royale_strlen<char>(char *param_1)

{
  __uint64 _Var1;
  
                    /* 0x1f37  1405  ??$royale_strlen@D@royale@@YA_KPEBD@Z */
  if (param_1 == (char *)0x0) {
    return 0;
  }
  _Var1 = 0xffffffffffffffff;
  do {
    _Var1 = _Var1 + 1;
  } while (param_1[_Var1] != '\0');
  return _Var1;
}


/* ==================== ~ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> @ 180001f50  (5 bytes) ==================== */

/* public: virtual __cdecl coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> >::~ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::
~ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x1f50  2045
                       ??1?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ
                        */
  std::
  vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
  ::_Tidy((vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
           *)(this + 0x10));
  return;
}


/* ==================== move<royale::Pair<royale::ProcessingFlag,royale::Variant>&___ptr64> @ 180002054  (5 bytes) ==================== */

/* class royale::Pair<enum royale::ProcessingFlag,class royale::Variant> && __ptr64 __cdecl
   std::move<class royale::Pair<enum royale::ProcessingFlag,class royale::Variant> & __ptr64>(class
   royale::Pair<enum royale::ProcessingFlag,class royale::Variant> & __ptr64) */

Pair<royale::ProcessingFlag,royale::Variant> * __cdecl
std::move<royale::Pair<royale::ProcessingFlag,royale::Variant>&___ptr64>
          (Pair<enum_royale::ProcessingFlag,class_royale::Variant> *param_1)

{
                    /* 0x2054  1360
                       ??$move@AEAV?$Pair@W4ProcessingFlag@royale@@VVariant@2@@royale@@@std@@YA$$QEAV?$Pair@W4ProcessingFlag@royale@@VVariant@2@@royale@@AEAV12@@Z
                        */
  return (Pair<royale::ProcessingFlag,royale::Variant> *)param_1;
}


/* ==================== operator=<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>,void> @ 18000209a  (5 bytes) ==================== */

/* public: class std::unique_ptr<class coco::ConnectionManager,struct std::default_delete<class
   coco::ConnectionManager> > & __ptr64 __cdecl std::unique_ptr<class coco::ConnectionManager,struct
   std::default_delete<class coco::ConnectionManager> >::operator=<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> > >,void>(class std::unique_ptr<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> > > > && __ptr64) __ptr64 */

unique_ptr<class_coco::ConnectionManager,struct_std::default_delete<class_coco::ConnectionManager>_>
* __thiscall
std::unique_ptr<coco::ConnectionManager,std::default_delete<coco::ConnectionManager>_>::
operator=<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>,void>
          (unique_ptr<coco::ConnectionManager,std::default_delete<coco::ConnectionManager>_> *this,
          unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
          *param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
                    /* 0x209a  345
                       ??$?4V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@X@?$unique_ptr@VConnectionManager@coco@@U?$default_delete@VConnectionManager@coco@@@std@@@std@@QEAAAEAV01@$$QEAV?$unique_ptr@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@1@@Z
                        */
  uVar1 = *(undefined8 *)param_1;
  *(undefined8 *)param_1 = 0;
  puVar2 = *(undefined8 **)this;
  *(undefined8 *)this = uVar1;
  if (puVar2 != (undefined8 *)0x0) {
    (**(code **)*puVar2)(puVar2,1);
  }
  return (unique_ptr<class_coco::ConnectionManager,struct_std::default_delete<class_coco::ConnectionManager>_>
          *)this;
}


/* ==================== Data<std::shared_ptr<types::ImageFrame>_> @ 180002153  (5 bytes) ==================== */

/* public: __cdecl coco::Data<class std::shared_ptr<struct types::ImageFrame> >::Data<class
   std::shared_ptr<struct types::ImageFrame> >(unsigned __int64) __ptr64 */

Data<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::Data<std::shared_ptr<types::ImageFrame>_>::Data<std::shared_ptr<types::ImageFrame>_>
          (Data<std::shared_ptr<types::ImageFrame>_> *this,__uint64 param_1)

{
                    /* 0x2153  1484
                       ??0?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@_K@Z */
  *(undefined ***)this = BufferBase<std::shared_ptr<types::ImageFrame>_>::vftable;
  *(undefined4 *)(this + 8) = 0;
  this[0xc] = (Data<std::shared_ptr<types::ImageFrame>_>)0x0;
  ConnectionStatisticsBuilder::ConnectionStatisticsBuilder
            ((ConnectionStatisticsBuilder *)(this + 0x10));
  *(undefined ***)this = vftable;
  *(undefined8 *)(this + 0x118) = 0;
  *(undefined8 *)(this + 0x120) = 0;
  *(undefined8 *)(this + 0x38) = 1;
  *(undefined8 *)(this + 0x98) = 0x7ff0000000000000;
  *(undefined8 *)(this + 0xd8) = 0x7ff0000000000000;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  ConnectionStatisticsBuilder::ResetProducerStats((ConnectionStatisticsBuilder *)(this + 0x10));
  *(undefined8 *)(this + 0x80) = 0x7ff0000000000000;
  return this;
}


/* ==================== ~_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>,1> @ 18000215d  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> >,class std::_Deque_val<struct std::_Deque_simple_types<class
   std::shared_ptr<struct types::ImageFrame> > >,1>::~_Compressed_pair<class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> >,class std::_Deque_val<struct
   std::_Deque_simple_types<class std::shared_ptr<struct types::ImageFrame> > >,1>(void) __ptr64 */

void __thiscall
std::
_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>,1>
::
~_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>,1>
          (_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>,1>
           *this)

{
                    /* 0x215d  2108
                       ??1?$_Compressed_pair@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@std@@V?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@2@$00@std@@QEAA@XZ
                        */
  return;
}


/* ==================== unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_> @ 1800021a3  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > >
   >::unique_ptr<class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> > > >(class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64) __ptr64 */

unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
::
unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x21a3  1901
                       ??0?$unique_ptr@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== construct<std::shared_ptr<types::ImageFrame>,std::shared_ptr<struct_types::ImageFrame>_const&___ptr64> @ 1800021a8  (5 bytes) ==================== */

/* public: static void __cdecl std::_Default_allocator_traits<class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> > >::construct<class std::shared_ptr<struct
   types::ImageFrame>,class std::shared_ptr<struct types::ImageFrame> const & __ptr64>(class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> > & __ptr64,class
   std::shared_ptr<struct types::ImageFrame> * __ptr64 const,class std::shared_ptr<struct
   types::ImageFrame> const & __ptr64) */

void __cdecl
std::_Default_allocator_traits<std::allocator<std::shared_ptr<types::ImageFrame>_>_>::
construct<std::shared_ptr<types::ImageFrame>,std::shared_ptr<struct_types::ImageFrame>_const&___ptr64>
          (allocator<std::shared_ptr<types::ImageFrame>_> *param_1,
          shared_ptr<types::ImageFrame> *param_2,shared_ptr<struct_types::ImageFrame> *param_3)

{
  _Ref_count_base *p_Var1;
  ImageFrame *pIVar2;
  
                    /* 0x21a8  931
                       ??$construct@V?$shared_ptr@UImageFrame@types@@@std@@AEBV12@@?$_Default_allocator_traits@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@SAXAEAV?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@1@QEAV?$shared_ptr@UImageFrame@types@@@1@AEBV31@@Z
                        */
  *(undefined8 *)param_2 = 0;
  *(undefined8 *)(param_2 + 8) = 0;
  p_Var1 = *(_Ref_count_base **)(param_3 + 8);
  pIVar2 = *(ImageFrame **)param_3;
  if (p_Var1 != (_Ref_count_base *)0x0) {
    LOCK();
    *(int *)(p_Var1 + 8) = *(int *)(p_Var1 + 8) + 1;
    UNLOCK();
  }
  _Ptr_base<types::ImageFrame>::_Reset0((_Ptr_base<types::ImageFrame> *)param_2,pIVar2,p_Var1);
  return;
}


/* ==================== Buffer<std::shared_ptr<types::ImageFrame>_> @ 1800021e4  (5 bytes) ==================== */

/* public: __cdecl coco::Buffer<class std::shared_ptr<struct types::ImageFrame> >::Buffer<class
   std::shared_ptr<struct types::ImageFrame> >(unsigned __int64) __ptr64 */

Buffer<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::Buffer<std::shared_ptr<types::ImageFrame>_>::Buffer<std::shared_ptr<types::ImageFrame>_>
          (Buffer<std::shared_ptr<types::ImageFrame>_> *this,__uint64 param_1)

{
  Buffer<std::shared_ptr<types::ImageFrame>_> *pBVar1;
  undefined8 *puVar2;
  
                    /* 0x21e4  1425
                       ??0?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@_K@Z */
  *(undefined ***)this = BufferBase<std::shared_ptr<types::ImageFrame>_>::vftable;
  *(undefined4 *)(this + 8) = 0;
  this[0xc] = (Buffer<std::shared_ptr<types::ImageFrame>_>)0x0;
  ConnectionStatisticsBuilder::ConnectionStatisticsBuilder
            ((ConnectionStatisticsBuilder *)(this + 0x10));
  *(undefined ***)this = vftable;
  pBVar1 = this + 0x118;
  *(undefined8 *)pBVar1 = 0;
  *(undefined8 *)(this + 0x120) = 0;
  *(undefined8 *)(this + 0x128) = 0;
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined8 *)(this + 0x138) = 0;
  puVar2 = (undefined8 *)thunk_FUN_180084ee4(0x10);
  if (puVar2 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
    _invalid_parameter_noinfo_noreturn();
  }
  *(undefined8 **)pBVar1 = puVar2;
  *puVar2 = 0;
  puVar2[1] = 0;
  **(undefined8 **)pBVar1 = pBVar1;
  *(__uint64 *)(this + 0x140) = param_1;
  *(__uint64 *)(this + 0x38) = param_1;
  *(undefined8 *)(this + 0x98) = 0x7ff0000000000000;
  *(undefined8 *)(this + 0xd8) = 0x7ff0000000000000;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  ConnectionStatisticsBuilder::ResetProducerStats((ConnectionStatisticsBuilder *)(this + 0x10));
  *(undefined8 *)(this + 0x80) = 0x7ff0000000000000;
  return this;
}


/* ==================== OutputPort<std::shared_ptr<types::ImageFrame>_> @ 18000221b  (5 bytes) ==================== */

/* public: __cdecl coco::OutputPort<class std::shared_ptr<struct types::ImageFrame>
   >::OutputPort<class std::shared_ptr<struct types::ImageFrame> >(class coco::Task * __ptr64,class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &
   __ptr64) __ptr64 */

OutputPort<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::
OutputPort<std::shared_ptr<types::ImageFrame>_>
          (OutputPort<std::shared_ptr<types::ImageFrame>_> *this,Task *param_1,
          basic_string<char,std::char_traits<char>,std::allocator<char>_> *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
                    /* 0x221b  1510
                       ??0?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@PEAVTask@1@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
                        */
  coco::PortBase::PortBase((PortBase *)this,param_1,param_2,1,false);
  *(undefined ***)this = vftable;
  puVar2 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar2 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    puVar2[1] = 0;
    *(undefined1 *)(puVar2 + 1) = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0;
    *puVar2 = ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
  }
  puVar1 = *(undefined8 **)(this + 8);
  *(undefined8 **)(this + 8) = puVar2;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(this + 0x60) = *(undefined8 *)(this + 8);
  return this;
}


/* ==================== default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_><coco::Data<std::shared_ptr<types::ImageFrame>_>,void> @ 180002261  (5 bytes) ==================== */

/* public: __cdecl std::default_delete<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> > >::default_delete<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> > ><class coco::Data<class std::shared_ptr<struct types::ImageFrame>
   >,void>(struct std::default_delete<class coco::Data<class std::shared_ptr<struct
   types::ImageFrame> > > const & __ptr64) __ptr64 */

default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>::
default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_><coco::Data<std::shared_ptr<types::ImageFrame>_>,void>
          (default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_> *this,
          default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_> *param_1)

{
                    /* 0x2261  265
                       ??$?0V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@X@?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@AEBU?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@1@@Z
                        */
  return this;
}


/* ==================== unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_> @ 180002333  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class RoyaleDataListener,struct std::default_delete<class
   RoyaleDataListener> >::unique_ptr<class RoyaleDataListener,struct std::default_delete<class
   RoyaleDataListener> >(class RoyaleDataListener * __ptr64) __ptr64 */

unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_> * __thiscall
std::unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_>::
unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_>
          (unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_> *this,
          RoyaleDataListener *param_1)

{
                    /* 0x2333  1918
                       ??0?$unique_ptr@VRoyaleDataListener@@U?$default_delete@VRoyaleDataListener@@@std@@@std@@QEAA@PEAVRoyaleDataListener@@@Z
                        */
  *(RoyaleDataListener **)this = param_1;
  return this;
}


/* ==================== ~_Deque_alloc<std::_Deque_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_> @ 180002397  (5 bytes) ==================== */

/* public: __cdecl std::_Deque_alloc<struct std::_Deque_base_types<class std::shared_ptr<struct
   types::ImageFrame>,class std::allocator<class std::shared_ptr<struct types::ImageFrame> > >
   >::~_Deque_alloc<struct std::_Deque_base_types<class std::shared_ptr<struct
   types::ImageFrame>,class std::allocator<class std::shared_ptr<struct types::ImageFrame> > >
   >(void) __ptr64 */

void __thiscall
std::
_Deque_alloc<std::_Deque_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
::
~_Deque_alloc<std::_Deque_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
          (_Deque_alloc<std::_Deque_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
                    /* 0x2397  2115
                       ??1?$_Deque_alloc@U?$_Deque_base_types@V?$shared_ptr@UImageFrame@types@@@std@@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@@std@@QEAA@XZ
                        */
  FUN_180002658(*(undefined8 *)this);
  *(undefined8 *)this = 0;
  return;
}


/* ==================== _Uninitialized_move<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>_>_> @ 1800023c9  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 __cdecl std::_Uninitialized_move<class
   std::shared_ptr<struct types::ImageFrame> * __ptr64,class std::shared_ptr<struct
   types::ImageFrame> * __ptr64,class std::allocator<class std::shared_ptr<struct types::ImageFrame>
   > >(class std::shared_ptr<struct types::ImageFrame> * __ptr64,class std::shared_ptr<struct
   types::ImageFrame> * __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> > & __ptr64) */

shared_ptr<types::ImageFrame> * __cdecl
std::
_Uninitialized_move<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
          (shared_ptr<struct_types::ImageFrame> *param_1,
          shared_ptr<struct_types::ImageFrame> *param_2,
          shared_ptr<struct_types::ImageFrame> *param_3,
          allocator<std::shared_ptr<types::ImageFrame>_> *param_4)

{
  shared_ptr<types::ImageFrame> *psVar1;
  
                    /* 0x23c9  745
                       ??$_Uninitialized_move@PEAV?$shared_ptr@UImageFrame@types@@@std@@PEAV12@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@YAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAV10@00AEAV?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@0@@Z
                        */
  psVar1 = _Uninitialized_move_al_unchecked<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
                     ();
  return psVar1;
}


/* ==================== ~vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_> @ 180002432  (5 bytes) ==================== */

/* public: __cdecl std::vector<class std::shared_ptr<struct types::ImageFrame>,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> > >::~vector<class
   std::shared_ptr<struct types::ImageFrame>,class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

void __thiscall
std::vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
::~vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
          (vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
           *this)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  
                    /* 0x2432  2398
                       ??1?$vector@V?$shared_ptr@UImageFrame@types@@@std@@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@QEAA@XZ
                        */
  if (*(shared_ptr<types::ImageFrame> **)this != (shared_ptr<types::ImageFrame> *)0x0) {
    _Destroy_range<std::allocator<std::shared_ptr<types::ImageFrame>_>_>
              (*(shared_ptr<types::ImageFrame> **)this,*(shared_ptr<types::ImageFrame> **)(this + 8)
               ,(allocator<std::shared_ptr<types::ImageFrame>_> *)this);
    uVar1 = *(ulonglong *)this;
    uVar2 = (longlong)(*(longlong *)(this + 0x10) - uVar1) >> 4;
    if ((0xfffffffffffffff < uVar2) ||
       ((uVar3 = uVar1, 0xfff < uVar2 << 4 &&
        ((((uVar1 & 0x1f) != 0 || (uVar3 = *(ulonglong *)(uVar1 - 8), uVar1 <= uVar3)) ||
         (0x1f < (uVar1 - uVar3) - 8)))))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar3);
    *(undefined8 *)this = 0;
    *(undefined8 *)(this + 8) = 0;
    *(undefined8 *)(this + 0x10) = 0;
  }
  return;
}


/* ==================== move<std::_Func_class<void,royale::DepthData_const*___ptr64>&___ptr64> @ 180002446  (5 bytes) ==================== */

/* class std::_Func_class<void,struct royale::DepthData const * __ptr64> && __ptr64 __cdecl
   std::move<class std::_Func_class<void,struct royale::DepthData const * __ptr64> & __ptr64>(class
   std::_Func_class<void,struct royale::DepthData const * __ptr64> & __ptr64) */

_Func_class<void,royale::DepthData_const*___ptr64> * __cdecl
std::move<std::_Func_class<void,royale::DepthData_const*___ptr64>&___ptr64>
          (_Func_class<void,struct_royale::DepthData_const*___ptr64> *param_1)

{
                    /* 0x2446  1371
                       ??$move@AEAV?$_Func_class@XPEBUDepthData@royale@@@std@@@std@@YA$$QEAV?$_Func_class@XPEBUDepthData@royale@@@0@AEAV10@@Z
                        */
  return (_Func_class<void,royale::DepthData_const*___ptr64> *)param_1;
}


/* ==================== _Deque_const_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_> @ 180002478  (5 bytes) ==================== */

/* public: __cdecl std::_Deque_const_iterator<class std::_Deque_val<struct
   std::_Deque_simple_types<class std::shared_ptr<struct types::ImageFrame> > >
   >::_Deque_const_iterator<class std::_Deque_val<struct std::_Deque_simple_types<class
   std::shared_ptr<struct types::ImageFrame> > > >(unsigned __int64,struct std::_Container_base12
   const * __ptr64) __ptr64 */

_Deque_const_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Deque_const_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Deque_const_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
          (_Deque_const_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,__uint64 param_1,_Container_base12 *param_2)

{
                    /* 0x2478  1583
                       ??0?$_Deque_const_iterator@V?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@@std@@QEAA@_KPEBU_Container_base12@1@@Z
                        */
  *(__uint64 *)(this + 0x10) = param_1;
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  if (param_2 != (_Container_base12 *)0x0) {
    *(undefined8 *)this = *(undefined8 *)param_2;
  }
  return this;
}


/* ==================== make_unique<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,void> @ 18000249b  (5 bytes) ==================== */

/* class std::unique_ptr<class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> > > > __cdecl std::make_unique<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame>
   >,void>(void) */

void __cdecl
std::make_unique<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,void>
          (void)

{
  undefined8 *puVar1;
  undefined8 *in_RCX;
  
                    /* 0x249b  1332
                       ??$make_unique@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$$VX@std@@YA?AV?$unique_ptr@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@0@XZ
                        */
  puVar1 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar1 == (undefined8 *)0x0) {
    *in_RCX = 0;
    return;
  }
  puVar1[1] = 0;
  *(undefined1 *)(puVar1 + 1) = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  *puVar1 = coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
  *in_RCX = puVar1;
  return;
}


/* ==================== ~CircularBuffer<std::shared_ptr<types::ImageFrame>_> @ 1800024a0  (5 bytes) ==================== */

/* public: virtual __cdecl coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame>
   >::~CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>::
~CircularBuffer<std::shared_ptr<types::ImageFrame>_>
          (CircularBuffer<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x24a0  2035
                       ??1?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ */
  std::
  deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>::
  _Tidy((deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
         *)(this + 0x118));
  FUN_180002658(*(undefined8 *)(this + 0x118));
  *(undefined8 *)(this + 0x118) = 0;
  std::vector<unsigned___int64,std::allocator<unsigned___int64>_>::_Tidy
            ((vector<unsigned___int64,std::allocator<unsigned___int64>_> *)(this + 0x100));
  std::
  deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
  ::
  ~deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
            ((deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
              *)(this + 0x10));
  return;
}


/* ==================== _Destroy_range1<std::allocator<std::shared_ptr<types::ImageFrame>_>_> @ 18000259f  (5 bytes) ==================== */

/* void __cdecl std::_Destroy_range1<class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> > >(class std::shared_ptr<struct types::ImageFrame> * __ptr64,class
   std::shared_ptr<struct types::ImageFrame> * __ptr64,class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> > & __ptr64,struct std::integral_constant<bool,0>) */

void __cdecl
std::_Destroy_range1<std::allocator<std::shared_ptr<types::ImageFrame>_>_>
          (longlong *param_1,longlong *param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong *plVar6;
  
                    /* 0x259f  484
                       ??$_Destroy_range1@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@YAXPEAV?$shared_ptr@UImageFrame@types@@@0@0AEAV?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@0@U?$integral_constant@_N$0A@@0@@Z
                        */
  if (param_1 != param_2) {
    plVar6 = param_1 + 1;
    do {
      plVar4 = (longlong *)*plVar6;
      if (plVar4 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar4 + 1;
        lVar5 = *plVar1;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)lVar5 == 1) {
          (**(code **)*plVar4)(plVar4);
          LOCK();
          piVar2 = (int *)((longlong)plVar4 + 0xc);
          iVar3 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar3 == 1) {
            (**(code **)(*plVar4 + 8))(plVar4);
          }
        }
      }
      plVar4 = plVar6 + 1;
      plVar6 = plVar6 + 2;
    } while (plVar4 != param_2);
  }
  return;
}


/* ==================== ConnectionTyped<std::shared_ptr<types::ImageFrame>_> @ 1800025fe  (5 bytes) ==================== */

/* public: __cdecl coco::ConnectionTyped<class std::shared_ptr<struct types::ImageFrame>
   >::ConnectionTyped<class std::shared_ptr<struct types::ImageFrame> >(class coco::PortBase *
   __ptr64,class coco::PortBase * __ptr64,struct coco::ConnectionPolicy const & __ptr64) __ptr64 */

ConnectionTyped<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::
ConnectionTyped<std::shared_ptr<types::ImageFrame>_>
          (ConnectionTyped<std::shared_ptr<types::ImageFrame>_> *this,PortBase *param_1,
          PortBase *param_2,ConnectionPolicy *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
                    /* 0x25fe  1477
                       ??0?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@PEAVPortBase@1@0AEBUConnectionPolicy@1@@Z
                        */
  uVar1 = *(undefined4 *)param_3;
  uVar2 = *(undefined4 *)(param_3 + 4);
  uVar3 = *(undefined4 *)(param_3 + 8);
  uVar4 = *(undefined4 *)(param_3 + 0xc);
  *(PortBase **)(this + 8) = param_1;
  *(PortBase **)(this + 0x10) = param_2;
  *(undefined4 *)(this + 0x18) = uVar1;
  *(undefined4 *)(this + 0x1c) = uVar2;
  *(undefined4 *)(this + 0x20) = uVar3;
  *(undefined4 *)(this + 0x24) = uVar4;
  *(undefined8 *)(this + 0x28) = 0;
  this[0x30] = (ConnectionTyped<std::shared_ptr<types::ImageFrame>_>)0x0;
  *(undefined ***)this = vftable;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  _Mtx_init_in_situ(this + 0x48,2,param_2,param_3,0xfffffffffffffffe);
  _Cnd_init_in_situ(this + 0x98);
  CreateConnection(this);
  return this;
}


/* ==================== unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_> @ 18000265d  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> > > >::unique_ptr<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > > >(void) __ptr64 */

unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
::
unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
                    /* 0x265d  1884
                       ??0?$unique_ptr@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  return this;
}


/* ==================== _Compressed_pair<std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 1800026d0  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > >,class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,1>::_Compressed_pair<struct std::default_delete<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > >,class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,1><class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> > * __ptr64 & __ptr64>(struct std::_Zero_then_variadic_args_t,class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64) __ptr64 */

_Compressed_pair<std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
* __thiscall
std::
_Compressed_pair<std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
::
_Compressed_pair<std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x26d0  45
                       ??$?0AEAPEAV?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Compressed_pair@U?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@PEAV?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAV?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_> @ 180002711  (5 bytes) ==================== */

/* public: __cdecl coco::ConnectionManagerTyped<class std::shared_ptr<struct types::ImageFrame>
   >::ConnectionManagerTyped<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_>::
ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x2711  1471
                       ??0?$ConnectionManagerTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@XZ
                        */
  this[8] = (ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_>)0x0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined ***)this = vftable;
  return this;
}


/* ==================== _Ptr_base<coco::ConnectionBase><coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> @ 18000272f  (5 bytes) ==================== */

/* public: __cdecl std::_Ptr_base<class coco::ConnectionBase>::_Ptr_base<class
   coco::ConnectionBase><class coco::ConnectionTyped<class std::shared_ptr<struct types::ImageFrame>
   > >(class std::_Ptr_base<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > > && __ptr64) __ptr64 */

_Ptr_base<coco::ConnectionBase> * __thiscall
std::_Ptr_base<coco::ConnectionBase>::
_Ptr_base<coco::ConnectionBase><coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
          (_Ptr_base<coco::ConnectionBase> *this,
          _Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *param_1)

{
                    /* 0x272f  256
                       ??$?0V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Ptr_base@VConnectionBase@coco@@@std@@QEAA@$$QEAV?$_Ptr_base@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@1@@Z
                        */
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  return this;
}


/* ==================== forward<coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64> @ 1800028fb  (5 bytes) ==================== */

/* class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 && __ptr64
   __cdecl std::forward<class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64>(class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64) */

OutputPort<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::forward<coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64>
          (OutputPort<class_std::shared_ptr<struct_types::ImageFrame>_> **param_1)

{
                    /* 0x28fb  1177
                       ??$forward@PEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YA$$QEAPEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (OutputPort<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== default_delete<coco::ConnectionManager><coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,void> @ 180002914  (5 bytes) ==================== */

/* public: __cdecl std::default_delete<class coco::ConnectionManager>::default_delete<class
   coco::ConnectionManager><class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,void>(struct std::default_delete<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > > const &
   __ptr64) __ptr64 */

default_delete<coco::ConnectionManager> * __thiscall
std::default_delete<coco::ConnectionManager>::
default_delete<coco::ConnectionManager><coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,void>
          (default_delete<coco::ConnectionManager> *this,
          default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>
          *param_1)

{
                    /* 0x2914  240
                       ??$?0V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@X@?$default_delete@VConnectionManager@coco@@@std@@QEAA@AEBU?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@1@@Z
                        */
  return this;
}


/* ==================== _Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64><std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_const&___ptr64,void> @ 180002969  (5 bytes) ==================== */

/* public: __cdecl std::_Func_impl_no_alloc<class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64>,void,struct
   royale::DepthData const * __ptr64>::_Func_impl_no_alloc<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64>,void,struct royale::DepthData const * __ptr64><class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> const & __ptr64,void>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> const & __ptr64)
   __ptr64 */

_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
* __thiscall
std::
_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
::
_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64><std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_const&___ptr64,void>
          (_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
           *this,_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
                 *param_1)

{
                    /* 0x2969  102
                       ??$?0AEBV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@X@?$_Func_impl_no_alloc@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@XPEBUDepthData@royale@@@std@@QEAA@AEBV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@1@@Z
                        */
  *(undefined ***)this = vftable;
  *(undefined8 *)(this + 8) = *(undefined8 *)param_1;
  this[0x10] = *(_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
                 *)(param_1 + 8);
  *(undefined8 *)(this + 0x18) = *(undefined8 *)(param_1 + 0x10);
  return this;
}


/* ==================== _Unfancy<std::shared_ptr<types::ImageFrame>_> @ 18000299b  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 __cdecl std::_Unfancy<class
   std::shared_ptr<struct types::ImageFrame> >(class std::shared_ptr<struct types::ImageFrame> *
   __ptr64) */

shared_ptr<types::ImageFrame> * __cdecl
std::_Unfancy<std::shared_ptr<types::ImageFrame>_>(shared_ptr<struct_types::ImageFrame> *param_1)

{
                    /* 0x299b  711
                       ??$_Unfancy@V?$shared_ptr@UImageFrame@types@@@std@@@std@@YAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAV10@@Z
                        */
  return (shared_ptr<types::ImageFrame> *)param_1;
}


/* ==================== addressof<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_const_> @ 1800029b4  (5 bytes) ==================== */

/* class std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64> const * __ptr64 __cdecl std::addressof<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> const >(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> const & __ptr64) */

_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
* __cdecl std::
          addressof<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_const_>
                    (_Binder<struct_std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(struct_royale::DepthData_const*___ptr64)___ptr64,class_meta::blocks::DeviceStreamBlock*___ptr64,struct_std::_Ph<1>_const&___ptr64>
                     *param_1)

{
                    /* 0x29b4  791
                       ??$addressof@$$CBV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@@std@@YAPEBV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@AEBV10@@Z
                        */
  return (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          *)param_1;
}


/* ==================== deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_> @ 180002a90  (5 bytes) ==================== */

/* public: __cdecl std::deque<class std::shared_ptr<struct types::ImageFrame>,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> > >::deque<class
   std::shared_ptr<struct types::ImageFrame>,class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_> *
__thiscall
std::deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
::deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
          (deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x2a90  1773
                       ??0?$deque@V?$shared_ptr@UImageFrame@types@@@std@@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  puVar1 = (undefined8 *)thunk_FUN_180084ee4(0x10);
  if (puVar1 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
    _invalid_parameter_noinfo_noreturn();
  }
  *(undefined8 **)this = puVar1;
  *puVar1 = 0;
  puVar1[1] = 0;
  **(undefined8 **)this = this;
  return this;
}


/* ==================== forward<royale::IDepthDataListener*___ptr64&___ptr64> @ 180002aa9  (5 bytes) ==================== */

/* class royale::IDepthDataListener * __ptr64 & __ptr64 __cdecl std::forward<class
   royale::IDepthDataListener * __ptr64 & __ptr64>(class royale::IDepthDataListener * __ptr64 &
   __ptr64) */

IDepthDataListener ** __cdecl
std::forward<royale::IDepthDataListener*___ptr64&___ptr64>(IDepthDataListener **param_1)

{
                    /* 0x2aa9  1088
                       ??$forward@AEAPEAVIDepthDataListener@royale@@@std@@YAAEAPEAVIDepthDataListener@royale@@AEAPEAV12@@Z
                        */
  return param_1;
}


/* ==================== vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_> @ 180002abd  (5 bytes) ==================== */

/* public: __cdecl std::vector<class std::shared_ptr<struct types::ImageFrame>,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> > >::vector<class
   std::shared_ptr<struct types::ImageFrame>,class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_> *
__thiscall
std::vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
::vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
          (vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
           *this)

{
                    /* 0x2abd  1932
                       ??0?$vector@V?$shared_ptr@UImageFrame@types@@@std@@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  return this;
}


/* ==================== forward<std::default_delete<RoyaleDataListener>_> @ 180002ae0  (5 bytes) ==================== */

/* struct std::default_delete<class RoyaleDataListener> && __ptr64 __cdecl std::forward<struct
   std::default_delete<class RoyaleDataListener> >(struct std::default_delete<class
   RoyaleDataListener> & __ptr64) */

default_delete<RoyaleDataListener> * __cdecl
std::forward<std::default_delete<RoyaleDataListener>_>
          (default_delete<class_RoyaleDataListener> *param_1)

{
                    /* 0x2ae0  1217
                       ??$forward@U?$default_delete@VRoyaleDataListener@@@std@@@std@@YA$$QEAU?$default_delete@VRoyaleDataListener@@@0@AEAU10@@Z
                        */
  return (default_delete<RoyaleDataListener> *)param_1;
}


/* ==================== _Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64><std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void> @ 180002b62  (5 bytes) ==================== */

/* public: __cdecl std::_Func_impl_no_alloc<class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64>,void,struct
   royale::DepthData const * __ptr64>::_Func_impl_no_alloc<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64>,void,struct royale::DepthData const * __ptr64><class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64>,void>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> && __ptr64) __ptr64
    */

_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
* __thiscall
std::
_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
::
_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64><std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void>
          (_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
           *this,_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
                 *param_1)

{
                    /* 0x2b62  283
                       ??$?0V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@X@?$_Func_impl_no_alloc@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@XPEBUDepthData@royale@@@std@@QEAA@$$QEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@1@@Z
                        */
  *(undefined ***)this = vftable;
  *(undefined8 *)(this + 8) = *(undefined8 *)param_1;
  this[0x10] = *(_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
                 *)(param_1 + 8);
  *(undefined8 *)(this + 0x18) = *(undefined8 *)(param_1 + 0x10);
  return this;
}


/* ==================== forward<royale::ProcessingFlag> @ 180002b76  (5 bytes) ==================== */

/* enum royale::ProcessingFlag && __ptr64 __cdecl std::forward<enum royale::ProcessingFlag>(enum
   royale::ProcessingFlag & __ptr64) */

ProcessingFlag * __cdecl std::forward<royale::ProcessingFlag>(ProcessingFlag *param_1)

{
                    /* 0x2b76  1250
                       ??$forward@W4ProcessingFlag@royale@@@std@@YA$$QEAW4ProcessingFlag@royale@@AEAW412@@Z
                        */
  return param_1;
}


/* ==================== _Uninitialized_value_construct_n1<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,unsigned___int64,std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_> @ 180002bbc  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 __cdecl
   std::_Uninitialized_value_construct_n1<class std::shared_ptr<struct types::ImageFrame> * __ptr64
   * __ptr64,unsigned __int64,class std::allocator<class std::shared_ptr<struct types::ImageFrame> *
   __ptr64> >(class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,unsigned
   __int64,class std::allocator<class std::shared_ptr<struct types::ImageFrame> * __ptr64> &
   __ptr64,struct std::integral_constant<bool,1>) */

shared_ptr<types::ImageFrame> ** __cdecl
std::
_Uninitialized_value_construct_n1<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,unsigned___int64,std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_>
          (void *param_1,longlong param_2)

{
                    /* 0x2bbc  760
                       ??$_Uninitialized_value_construct_n1@PEAPEAV?$shared_ptr@UImageFrame@types@@@std@@_KV?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@YAPEAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAPEAV10@_KAEAV?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@0@U?$integral_constant@_N$00@0@@Z
                        */
  memset(param_1,0,param_2 * 8);
  return (shared_ptr<types::ImageFrame> **)(param_2 * 8 + (longlong)param_1);
}


/* ==================== ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> @ 180002c02  (5 bytes) ==================== */

/* public: __cdecl coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> >::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> >(void) __ptr64 */

ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>::
ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x2c02  1465
                       ??0?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@XZ
                        */
  this[8] = (ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>)0x0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined ***)this = vftable;
  *(undefined8 *)(this + 0x28) = 0;
  return this;
}


/* ==================== _Call<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64,royale::DepthData_const*___ptr64> @ 180002c43  (5 bytes) ==================== */

/* public: static void __cdecl std::_Invoker_ret<void,1>::_Call<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> & __ptr64,struct royale::DepthData const * __ptr64>(class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> & __ptr64,struct royale::DepthData const * __ptr64 && __ptr64) */

void __cdecl
std::_Invoker_ret<void,1>::
_Call<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64,royale::DepthData_const*___ptr64>
          (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
           *param_1,DepthData **param_2)

{
                    /* 0x2c43  429
                       ??$_Call@AEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@PEBUDepthData@royale@@@?$_Invoker_ret@X$00@std@@SAXAEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@1@$$QEAPEBUDepthData@royale@@@Z
                        */
                    /* WARNING: Could not recover jumptable at 0x00018001a76a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)param_1)(*(undefined8 *)(param_1 + 0x10),*param_2);
  return;
}


/* ==================== ~Pair<royale::ProcessingFlag,royale::Variant> @ 180002c89  (5 bytes) ==================== */

/* public: virtual __cdecl royale::Pair<enum royale::ProcessingFlag,class
   royale::Variant>::~Pair<enum royale::ProcessingFlag,class royale::Variant>(void) __ptr64 */

void __thiscall
royale::Pair<royale::ProcessingFlag,royale::Variant>::~Pair<royale::ProcessingFlag,royale::Variant>
          (Pair<royale::ProcessingFlag,royale::Variant> *this)

{
                    /* 0x2c89  2099  ??1?$Pair@W4ProcessingFlag@royale@@VVariant@2@@royale@@UEAA@XZ
                        */
  *(undefined ***)this = vftable;
  royale::Variant::~Variant((Variant *)(this + 0xc));
  return;
}


/* ==================== _Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0> @ 180002cc5  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class std::tuple<class meta::blocks::DeviceStreamBlock
   * __ptr64,struct std::_Ph<1> >,0>::_Compressed_pair<void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   std::tuple<class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> >,0>(class
   std::_Compressed_pair<void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData
   const * __ptr64) __ptr64,class std::tuple<class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> >,0> const & __ptr64) __ptr64 */

_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
* __thiscall
std::
_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
::
_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
          (_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
           *this,_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(struct_royale::DepthData_const*___ptr64)___ptr64,class_std::tuple<class_meta::blocks::DeviceStreamBlock*___ptr64,struct_std::_Ph<1>_>,0>
                 *param_1)

{
                    /* 0x2cc5  1563
                       ??0?$_Compressed_pair@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZV?$tuple@PEAVDeviceStreamBlock@blocks@meta@@U?$_Ph@$00@std@@@std@@$0A@@std@@QEAA@AEBV01@@Z
                        */
  *(undefined8 *)this = *(undefined8 *)param_1;
  this[8] = *(_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
              *)(param_1 + 8);
  *(undefined8 *)(this + 0x10) = *(undefined8 *)(param_1 + 0x10);
  return this;
}


/* ==================== tuple<royale::DepthData_const*___ptr64&&___ptr64><std::_Exact_args_t,royale::DepthData_const*___ptr64,0> @ 180002d15  (5 bytes) ==================== */

/* public: __cdecl std::tuple<struct royale::DepthData const * __ptr64 && __ptr64>::tuple<struct
   royale::DepthData const * __ptr64 && __ptr64><struct std::_Exact_args_t,struct royale::DepthData
   const * __ptr64,0>(struct std::_Exact_args_t,struct royale::DepthData const * __ptr64 && __ptr64)
   __ptr64 */

tuple<royale::DepthData_const*___ptr64&&___ptr64> * __thiscall
std::tuple<royale::DepthData_const*___ptr64&&___ptr64>::
tuple<royale::DepthData_const*___ptr64&&___ptr64><std::_Exact_args_t,royale::DepthData_const*___ptr64,0>
          (tuple<royale::DepthData_const*___ptr64&&___ptr64> *this,undefined8 param_2,
          undefined8 param_3)

{
                    /* 0x2d15  217
                       ??$?0U_Exact_args_t@std@@PEBUDepthData@royale@@$$V$0A@@?$tuple@$$QEAPEBUDepthData@royale@@@std@@QEAA@U_Exact_args_t@1@$$QEAPEBUDepthData@royale@@@Z
                        */
  *(undefined8 *)this = param_3;
  return this;
}


/* ==================== forward<std::function<void___cdecl(royale::DepthData_const*___ptr64)>&___ptr64> @ 180002d60  (5 bytes) ==================== */

/* class std::function<void __cdecl(struct royale::DepthData const * __ptr64)> & __ptr64 __cdecl
   std::forward<class std::function<void __cdecl(struct royale::DepthData const * __ptr64)> &
   __ptr64>(class std::function<void __cdecl(struct royale::DepthData const * __ptr64)> & __ptr64)
    */

function<void___cdecl(royale::DepthData_const*___ptr64)> * __cdecl
std::forward<std::function<void___cdecl(royale::DepthData_const*___ptr64)>&___ptr64>
          (function<void___cdecl(struct_royale::DepthData_const*___ptr64)> *param_1)

{
                    /* 0x2d60  1111
                       ??$forward@AEAV?$function@$$A6AXPEBUDepthData@royale@@@Z@std@@@std@@YAAEAV?$function@$$A6AXPEBUDepthData@royale@@@Z@0@AEAV10@@Z
                        */
  return (function<void___cdecl(royale::DepthData_const*___ptr64)> *)param_1;
}


/* ==================== forward<std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_> @ 180002d83  (5 bytes) ==================== */

/* struct std::default_delete<class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> > > && __ptr64 __cdecl std::forward<struct
   std::default_delete<class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> > > >(struct std::default_delete<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > > &
   __ptr64) */

default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_> * __cdecl
std::
forward<std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
          (default_delete<class_coco::ConnectionManagerOutputScatter<class_std::shared_ptr<struct_types::ImageFrame>_>_>
           *param_1)

{
                    /* 0x2d83  1208
                       ??$forward@U?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@YA$$QEAU?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@0@AEAU10@@Z
                        */
  return (default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>
          *)param_1;
}


/* ==================== _Compressed_pair<std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180002db0  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > >,class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,1>::_Compressed_pair<struct std::default_delete<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > >,class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,1><class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> > * __ptr64 & __ptr64>(struct std::_Zero_then_variadic_args_t,class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > * __ptr64
   & __ptr64) __ptr64 */

_Compressed_pair<std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
* __thiscall
std::
_Compressed_pair<std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
::
_Compressed_pair<std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x2db0  51
                       ??$?0AEAPEAV?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Compressed_pair@U?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@PEAV?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAV?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== CheckPortFps<std::shared_ptr<types::ImageFrame>_> @ 180002e05  (5 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: void __cdecl meta::blocks::DeviceStatusBlock::CheckPortFps<class std::shared_ptr<struct
   types::ImageFrame> >(class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > &
   __ptr64,int,int) __ptr64 */

void __thiscall
meta::blocks::DeviceStatusBlock::CheckPortFps<std::shared_ptr<types::ImageFrame>_>
          (DeviceStatusBlock *this,InputPort<std::shared_ptr<types::ImageFrame>_> *param_1,
          int param_2,int param_3)

{
  __uint64 *p_Var1;
  undefined8 *puVar2;
  double dVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  int iVar10;
  uint uVar11;
  PortBase *pPVar12;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar13;
  ulonglong uVar14;
  char *pcVar15;
  LogMessage *pLVar16;
  basic_ostream<char,std::char_traits<char>_> *pbVar17;
  shared_ptr<types::ImageFrame> *psVar18;
  longlong lVar19;
  undefined8 *puVar20;
  InputPort<std::shared_ptr<types::ImageFrame>_> *pIVar21;
  ulonglong uVar22;
  undefined1 auStack_d8 [32];
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  double dStack_b0;
  shared_ptr<types::ImageFrame> *psStack_a8;
  shared_ptr<types::ImageFrame> *psStack_a0;
  longlong lStack_98;
  LogMessage aLStack_90 [16];
  undefined8 uStack_80;
  ulonglong auStack_78 [3];
  ulonglong uStack_60;
  ulonglong uStack_58;
  
                    /* 0x2e05  391
                       ??$CheckPortFps@V?$shared_ptr@UImageFrame@types@@@std@@@DeviceStatusBlock@blocks@meta@@QEAAXAEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@HH@Z
                        */
  uStack_80 = 0xfffffffffffffffe;
  uStack_58 = DAT_1802450f8 ^ (ulonglong)auStack_d8;
  uVar22 = (ulonglong)param_3;
  bVar9 = false;
  bVar8 = false;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  bVar4 = false;
  uStack_b8 = 0;
  puVar20 = *(undefined8 **)(*(longlong *)(param_1 + 8) + 0x10);
  puVar2 = *(undefined8 **)(*(longlong *)(param_1 + 8) + 0x18);
  while( true ) {
    if (puVar20 == puVar2) {
      if (0 < *(int *)FLAGS_v_exref) {
        pcVar15 = (char *)FUN_180075170(auStack_78);
        uStack_b8 = 0x10;
        pLVar16 = (LogMessage *)
                  google::LogMessage::LogMessage
                            (aLStack_90,
                             "d:\\jenkins\\workspace\\sdk2_release_2.7.0-production\\jupiter\\meta_core\\blocks\\device\\device_status_block.h"
                             ,0x5d);
        bVar9 = true;
        bVar8 = true;
        uStack_b8 = 0x30;
        pbVar17 = google::LogMessage::stream(pLVar16);
        p_Var1 = (__uint64 *)(pcVar15 + 0x10);
        if (0xf < *(ulonglong *)(pcVar15 + 0x18)) {
          pcVar15 = *(char **)pcVar15;
        }
        pbVar17 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                            ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,pcVar15,
                             *p_Var1);
        pIVar21 = param_1 + 0x18;
        pbVar17 = std::operator<<<std::char_traits<char>_>
                            ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,
                             "Input Port ");
        if (0xf < *(ulonglong *)(param_1 + 0x30)) {
          pIVar21 = *(InputPort<std::shared_ptr<types::ImageFrame>_> **)pIVar21;
        }
        pbVar17 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                            ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,
                             (char *)pIVar21,*(__uint64 *)(param_1 + 0x28));
        std::operator<<<std::char_traits<char>_>
                  ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17," has no new data."
                  );
      }
      if (bVar8) {
        google::LogMessage::~LogMessage(aLStack_90);
      }
      if ((bVar9) && (0xf < uStack_60)) {
        uVar14 = auStack_78[0];
        if ((0xfff < uStack_60 + 1) &&
           ((((auStack_78[0] & 0x1f) != 0 ||
             (uVar14 = *(ulonglong *)(auStack_78[0] - 8), auStack_78[0] <= uVar14)) ||
            (0x1f < (auStack_78[0] - uVar14) - 8)))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        FUN_180002658(uVar14);
      }
      if (uVar22 < 0xd) {
        *(uint *)(this + (uVar22 >> 5) * 4 + 600) =
             *(uint *)(this + (uVar22 >> 5) * 4 + 600) & ~(1 << (param_3 & 0x1fU));
        return;
      }
      std::bitset<13>::_Xran((bitset<13> *)(this + 600));
      return;
    }
    iVar10 = (**(code **)(*(longlong *)*puVar20 + 8))();
    if (iVar10 == 2) break;
    puVar20 = puVar20 + 2;
  }
  psStack_a8 = (shared_ptr<types::ImageFrame> *)0x0;
  psStack_a0 = (shared_ptr<types::ImageFrame> *)0x0;
  lStack_98 = 0;
  coco::ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_>::ReadAll
            (*(ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_> **)(param_1 + 0x60),
             (vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
              *)&psStack_a8);
  dStack_b0 = DAT_1800a14f8;
  lVar19 = (longlong)psStack_a0 - (longlong)psStack_a8 >> 4;
  iVar10 = (int)lVar19 + -1;
  dVar3 = *(double *)(*(longlong *)(psStack_a8 + (longlong)iVar10 * 0x10) + 8) -
          *(double *)(*(longlong *)psStack_a8 + 8);
  if (lVar19 == 1) {
    if (0 < *(int *)FLAGS_v_exref) {
      pcVar15 = (char *)FUN_180075170(auStack_78);
      uStack_b8 = 1;
      pLVar16 = (LogMessage *)
                google::LogMessage::LogMessage
                          (aLStack_90,
                           "d:\\jenkins\\workspace\\sdk2_release_2.7.0-production\\jupiter\\meta_core\\blocks\\device\\device_status_block.h"
                           ,0x40);
      bVar5 = true;
      bVar4 = true;
      uStack_b8 = 3;
      pbVar17 = google::LogMessage::stream(pLVar16);
      p_Var1 = (__uint64 *)(pcVar15 + 0x10);
      if (0xf < *(ulonglong *)(pcVar15 + 0x18)) {
        pcVar15 = *(char **)pcVar15;
      }
      pbVar17 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                          ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,pcVar15,
                           *p_Var1);
      pIVar21 = param_1 + 0x18;
      pbVar17 = std::operator<<<std::char_traits<char>_>
                          ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,
                           "Warning: Input Port ");
      if (0xf < *(ulonglong *)(param_1 + 0x30)) {
        pIVar21 = *(InputPort<std::shared_ptr<types::ImageFrame>_> **)pIVar21;
      }
      pbVar17 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                          ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,
                           (char *)pIVar21,*(__uint64 *)(param_1 + 0x28));
      std::operator<<<std::char_traits<char>_>
                ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,
                 " has only 1 data. Something is wrong");
    }
    if (bVar4) {
      google::LogMessage::~LogMessage(aLStack_90);
    }
    if ((!bVar5) || (uStack_60 < 0x10)) goto LAB_18006bfac;
    if (0xfff < uStack_60 + 1) {
      if ((((auStack_78[0] & 0x1f) != 0) ||
          (uVar14 = *(ulonglong *)(auStack_78[0] - 8), auStack_78[0] <= uVar14)) ||
         (0x1f < (auStack_78[0] - uVar14) - 8)) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
LAB_18006bfa4:
      auStack_78[0] = uVar14;
    }
  }
  else {
    if (dVar3 <= 0.0) goto LAB_18006bfac;
    dStack_b0 = (double)iVar10 / dVar3;
    pIVar21 = param_1 + 0x18;
    std::
    _Hash<std::_Umap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,std::_Uhash_compare<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>,0>_>
    ::find((_Hash<std::_Umap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,std::_Uhash_compare<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>,0>_>
            *)(this + 0xc20),
           (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)&uStack_b8);
    if (CONCAT44(uStack_b4,uStack_b8) != *(longlong *)(this + 0xc28)) {
      pPVar12 = coco::Task::GetPort((Task *)this,
                                    (basic_string<char,std::char_traits<char>,std::allocator<char>_>
                                     *)(CONCAT44(uStack_b4,uStack_b8) + 0x30));
      (**(code **)(**(longlong **)(pPVar12 + 0x60) + 8))(*(longlong **)(pPVar12 + 0x60),&dStack_b0);
    }
    if ((this[0xced] != (DeviceStatusBlock)0x0) && (1 < *(int *)FLAGS_v_exref)) {
      pcVar15 = (char *)FUN_180075170(auStack_78);
      uStack_b8 = 4;
      pLVar16 = (LogMessage *)
                google::LogMessage::LogMessage
                          (aLStack_90,
                           "d:\\jenkins\\workspace\\sdk2_release_2.7.0-production\\jupiter\\meta_core\\blocks\\device\\device_status_block.h"
                           ,0x4e);
      bVar7 = true;
      bVar6 = true;
      uStack_b8 = 0xc;
      lVar19 = (longlong)psStack_a0 - (longlong)psStack_a8;
      pbVar17 = google::LogMessage::stream(pLVar16);
      p_Var1 = (__uint64 *)(pcVar15 + 0x10);
      if (0xf < *(ulonglong *)(pcVar15 + 0x18)) {
        pcVar15 = *(char **)pcVar15;
      }
      pbVar17 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                          ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,pcVar15,
                           *p_Var1);
      pbVar17 = std::operator<<<std::char_traits<char>_>
                          ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,"Port ");
      if (0xf < *(ulonglong *)(param_1 + 0x30)) {
        pIVar21 = *(InputPort<std::shared_ptr<types::ImageFrame>_> **)pIVar21;
      }
      pbVar17 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                          ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17,
                           (char *)pIVar21,*(__uint64 *)(param_1 + 0x28));
      pbVar17 = std::operator<<<std::char_traits<char>_>
                          ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar17," FPS = ");
      pbVar13 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar17,dStack_b0);
      pbVar17 = std::operator<<<std::char_traits<char>_>(pbVar13," based on last ");
      pbVar13 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar17,lVar19 >> 4);
      pbVar17 = std::operator<<<std::char_traits<char>_>(pbVar13," frame(s). ");
      pbVar13 = std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar17,dVar3);
      std::basic_ostream<char,std::char_traits<char>_>::operator<<
                ((basic_ostream<char,std::char_traits<char>_> *)pbVar13,
                 std::endl<char,std::char_traits<char>_>);
    }
    if (bVar6) {
      google::LogMessage::~LogMessage(aLStack_90);
    }
    if ((!bVar7) || (uStack_60 < 0x10)) goto LAB_18006bfac;
    if (0xfff < uStack_60 + 1) {
      if ((((auStack_78[0] & 0x1f) != 0) ||
          (uVar14 = *(ulonglong *)(auStack_78[0] - 8), auStack_78[0] <= uVar14)) ||
         (0x1f < (auStack_78[0] - uVar14) - 8)) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      goto LAB_18006bfa4;
    }
  }
  FUN_180002658(auStack_78[0]);
LAB_18006bfac:
  if (dStack_b0 <= (double)param_2) {
    if (0xc < uVar22) {
      std::bitset<13>::_Xran((bitset<13> *)(this + 600));
      return;
    }
    uVar11 = *(uint *)(this + (uVar22 >> 5) * 4 + 600) & ~(1 << (param_3 & 0x1fU));
  }
  else {
    if (0xc < uVar22) {
      std::bitset<13>::_Xran((bitset<13> *)(this + 600));
      return;
    }
    uVar11 = *(uint *)(this + (uVar22 >> 5) * 4 + 600) | 1 << (param_3 & 0x1fU);
  }
  *(uint *)(this + (uVar22 >> 5) * 4 + 600) = uVar11;
  if (psStack_a8 == (shared_ptr<types::ImageFrame> *)0x0) {
    return;
  }
  std::_Destroy_range<std::allocator<std::shared_ptr<types::ImageFrame>_>_>
            (psStack_a8,psStack_a0,(allocator<std::shared_ptr<types::ImageFrame>_> *)&psStack_a8);
  uVar22 = lStack_98 - (longlong)psStack_a8 >> 4;
  if ((0xfffffffffffffff < uVar22) ||
     ((psVar18 = psStack_a8, 0xfff < uVar22 << 4 &&
      (((((ulonglong)psStack_a8 & 0x1f) != 0 ||
        (psVar18 = *(shared_ptr<types::ImageFrame> **)(psStack_a8 + -8), psStack_a8 <= psVar18)) ||
       ((shared_ptr<types::ImageFrame> *)0x1f < psStack_a8 + (-8 - (longlong)psVar18))))))) {
                    /* WARNING: Subroutine does not return */
    _invalid_parameter_noinfo_noreturn();
  }
  FUN_180002658(psVar18);
  return;
}


/* ==================== ~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_> @ 180002e19  (5 bytes) ==================== */

/* public: virtual __cdecl royale::Vector<class royale::Pair<enum royale::ProcessingFlag,class
   royale::Variant> >::~Vector<class royale::Pair<enum royale::ProcessingFlag,class royale::Variant>
   >(void) __ptr64 */

void __thiscall
royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>
          (Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_> *this)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  
                    /* 0x2e19  2100
                       ??1?$Vector@V?$Pair@W4ProcessingFlag@royale@@VVariant@2@@royale@@@royale@@UEAA@XZ
                        */
  *(undefined ***)this = vftable;
  clear(this);
  freeAllocation(this);
  plVar4 = *(longlong **)(this + 0x10);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}


/* ==================== make_shared<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>,coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64,coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64,coco::ConnectionPolicy&___ptr64> @ 180002ec8  (5 bytes) ==================== */

/* class std::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct types::ImageFrame>
   > > __cdecl std::make_shared<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> >,class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64,class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,struct coco::ConnectionPolicy & __ptr64>(class coco::InputPort<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64,class coco::OutputPort<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 && __ptr64,struct coco::ConnectionPolicy &
   __ptr64) */

InputPort<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::
make_shared<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>,coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64,coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64,coco::ConnectionPolicy&___ptr64>
          (InputPort<std::shared_ptr<types::ImageFrame>_> **param_1,
          OutputPort<std::shared_ptr<types::ImageFrame>_> **param_2,ConnectionPolicy *param_3)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  _Ref_count_base *p_Var6;
  undefined4 *in_R9;
  
                    /* 0x2ec8  1305
                       ??$make_shared@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@2@PEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@2@AEAUConnectionPolicy@2@@std@@YA?AV?$shared_ptr@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@0@AEAPEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$$QEAPEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@3@AEAUConnectionPolicy@3@@Z
                        */
  p_Var6 = (_Ref_count_base *)thunk_FUN_180084ee4(0xf0);
  if (p_Var6 == (_Ref_count_base *)0x0) {
    p_Var6 = (_Ref_count_base *)0x0;
  }
  else {
    *(undefined4 *)(p_Var6 + 8) = 1;
    *(undefined4 *)(p_Var6 + 0xc) = 1;
    *(undefined ***)p_Var6 =
         _Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::vftable;
    uVar1 = *(undefined8 *)param_3;
    uVar2 = *in_R9;
    uVar3 = in_R9[1];
    uVar4 = in_R9[2];
    uVar5 = in_R9[3];
    *(OutputPort<std::shared_ptr<types::ImageFrame>_> **)(p_Var6 + 0x18) = *param_2;
    *(undefined8 *)(p_Var6 + 0x20) = uVar1;
    *(undefined4 *)(p_Var6 + 0x28) = uVar2;
    *(undefined4 *)(p_Var6 + 0x2c) = uVar3;
    *(undefined4 *)(p_Var6 + 0x30) = uVar4;
    *(undefined4 *)(p_Var6 + 0x34) = uVar5;
    *(undefined8 *)(p_Var6 + 0x38) = 0;
    p_Var6[0x40] = (_Ref_count_base)0x0;
    *(undefined ***)(p_Var6 + 0x10) =
         coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::vftable;
    *(undefined8 *)(p_Var6 + 0x48) = 0;
    *(undefined8 *)(p_Var6 + 0x50) = 0;
    _Mtx_init_in_situ(p_Var6 + 0x58,2);
    _Cnd_init_in_situ(p_Var6 + 0xa8);
    coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::CreateConnection
              ((ConnectionTyped<std::shared_ptr<types::ImageFrame>_> *)(p_Var6 + 0x10));
  }
  *param_1 = (InputPort<std::shared_ptr<types::ImageFrame>_> *)0x0;
  param_1[1] = (InputPort<std::shared_ptr<types::ImageFrame>_> *)0x0;
  shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
  _Resetp0<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
            ((shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *)param_1,
             (ConnectionTyped<std::shared_ptr<types::ImageFrame>_> *)(p_Var6 + 0x10),p_Var6);
  return param_1;
}


/* ==================== operator=<std::function<void___cdecl(royale::DepthData_const*___ptr64)>&___ptr64,void> @ 180002ef0  (5 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: class std::function<void __cdecl(struct royale::DepthData const * __ptr64)> & __ptr64
   __cdecl std::function<void __cdecl(struct royale::DepthData const * __ptr64)>::operator=<class
   std::function<void __cdecl(struct royale::DepthData const * __ptr64)> & __ptr64,void>(class
   std::function<void __cdecl(struct royale::DepthData const * __ptr64)> & __ptr64) __ptr64 */

function<void___cdecl(struct_royale::DepthData_const*___ptr64)> * __thiscall
std::function<void___cdecl(royale::DepthData_const*___ptr64)>::
operator=<std::function<void___cdecl(royale::DepthData_const*___ptr64)>&___ptr64,void>
          (function<void___cdecl(royale::DepthData_const*___ptr64)> *this,
          function<void___cdecl(struct_royale::DepthData_const*___ptr64)> *param_1)

{
  undefined8 *puVar1;
  function<void___cdecl(royale::DepthData_const*___ptr64)> *pfVar2;
  undefined1 auStack_c8 [32];
  undefined8 uStack_a8;
  function<void___cdecl(royale::DepthData_const*___ptr64)> afStack_98 [56];
  function<void___cdecl(royale::DepthData_const*___ptr64)> *pfStack_60;
  _Func_class<void,struct_royale::DepthData_const*___ptr64> a_Stack_58 [56];
  function<void___cdecl(royale::DepthData_const*___ptr64)> *pfStack_20;
  ulonglong uStack_18;
  
                    /* 0x2ef0  316
                       ??$?4AEAV?$function@$$A6AXPEBUDepthData@royale@@@Z@std@@X@?$function@$$A6AXPEBUDepthData@royale@@@Z@std@@QEAAAEAV01@AEAV01@@Z
                        */
  uStack_a8 = 0xfffffffffffffffe;
  uStack_18 = DAT_1802450f8 ^ (ulonglong)auStack_c8;
  pfStack_60 = (function<void___cdecl(royale::DepthData_const*___ptr64)> *)0x0;
  puVar1 = *(undefined8 **)(param_1 + 0x38);
  if (puVar1 != (undefined8 *)0x0) {
    pfStack_60 = (function<void___cdecl(royale::DepthData_const*___ptr64)> *)
                 (**(code **)*puVar1)(puVar1,afStack_98);
  }
  if ((pfStack_60 != afStack_98) &&
     (pfVar2 = *(function<void___cdecl(royale::DepthData_const*___ptr64)> **)(this + 0x38),
     pfVar2 != this)) {
    *(function<void___cdecl(royale::DepthData_const*___ptr64)> **)(this + 0x38) = pfStack_60;
    pfStack_60 = pfVar2;
    goto LAB_180018697;
  }
  pfStack_20 = (function<void___cdecl(royale::DepthData_const*___ptr64)> *)0x0;
  if (pfStack_60 != (function<void___cdecl(royale::DepthData_const*___ptr64)> *)0x0) {
    if (pfStack_60 == afStack_98) {
      pfStack_20 = (function<void___cdecl(royale::DepthData_const*___ptr64)> *)
                   (**(code **)(*(longlong *)pfStack_60 + 8))(pfStack_60,a_Stack_58);
      if (pfStack_60 == (function<void___cdecl(royale::DepthData_const*___ptr64)> *)0x0)
      goto LAB_18001865a;
      (**(code **)(*(longlong *)pfStack_60 + 0x20))
                (pfStack_60,CONCAT71((int7)((ulonglong)afStack_98 >> 8),pfStack_60 != afStack_98));
    }
    else {
      pfStack_20 = pfStack_60;
    }
    pfStack_60 = (function<void___cdecl(royale::DepthData_const*___ptr64)> *)0x0;
  }
LAB_18001865a:
  _Func_class<void,royale::DepthData_const*___ptr64>::_Reset_move
            ((_Func_class<void,royale::DepthData_const*___ptr64> *)afStack_98,
             (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)this);
  _Func_class<void,royale::DepthData_const*___ptr64>::_Reset_move
            ((_Func_class<void,royale::DepthData_const*___ptr64> *)this,a_Stack_58);
  if (pfStack_20 != (function<void___cdecl(royale::DepthData_const*___ptr64)> *)0x0) {
    (**(code **)(*(longlong *)pfStack_20 + 0x20))
              (pfStack_20,
               CONCAT71((int7)((ulonglong)a_Stack_58 >> 8),
                        pfStack_20 !=
                        (function<void___cdecl(royale::DepthData_const*___ptr64)> *)a_Stack_58));
  }
LAB_180018697:
  if (pfStack_60 != (function<void___cdecl(royale::DepthData_const*___ptr64)> *)0x0) {
    (**(code **)(*(longlong *)pfStack_60 + 0x20))(pfStack_60,pfStack_60 != afStack_98);
  }
  return (function<void___cdecl(struct_royale::DepthData_const*___ptr64)> *)this;
}


/* ==================== forward<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180002f59  (5 bytes) ==================== */

/* class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64 __cdecl std::forward<class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64>(class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > * __ptr64
   & __ptr64) */

ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::
forward<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (ConnectionManagerOutputScatter<class_std::shared_ptr<struct_types::ImageFrame>_>
           **param_1)

{
                    /* 0x2f59  1066
                       ??$forward@AEAPEAV?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YAAEAPEAV?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== TofDataGrabber @ 180002f72  (5 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: void __cdecl meta::blocks::DeviceStreamBlock::TofDataGrabber(struct royale::DepthData
   const * __ptr64) __ptr64 */

void __thiscall
meta::blocks::DeviceStreamBlock::TofDataGrabber(DeviceStreamBlock *this,DepthData *param_1)

{
  Vector<royale::DepthPoint> *this_00;
  longlong *plVar1;
  int *piVar2;
  undefined4 uVar3;
  float fVar4;
  undefined4 uVar5;
  float fVar6;
  DeviceStreamBlock *pDVar7;
  __uint64 _Var8;
  DepthPoint *pDVar9;
  longlong lVar10;
  longlong lVar11;
  longlong lVar12;
  __uint64 _Var13;
  int iVar14;
  uint uVar15;
  double dVar16;
  undefined1 auStack_338 [32];
  undefined4 uStack_318;
  undefined8 *puStack_310;
  longlong *plStack_308;
  undefined8 *puStack_300;
  longlong *plStack_2f8;
  undefined8 *puStack_2f0;
  longlong *plStack_2e8;
  undefined8 *puStack_2e0;
  longlong *plStack_2d8;
  undefined8 *puStack_2d0;
  longlong *plStack_2c8;
  uint uStack_2c0;
  uint uStack_2bc;
  uint uStack_2b8;
  uint uStack_2b4;
  uint uStack_2b0;
  uint uStack_2ac;
  uint uStack_2a8;
  uint uStack_2a4;
  uint uStack_2a0;
  uint uStack_29c;
  longlong alStack_298 [2];
  undefined4 uStack_288;
  longlong alStack_280 [2];
  longlong alStack_270 [2];
  DepthData *apDStack_260 [2];
  DeviceStreamBlock *apDStack_250 [2];
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  longlong lStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  longlong lStack_200;
  undefined8 *puStack_1f8;
  undefined8 *puStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  longlong lStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  longlong lStack_1a0;
  undefined8 *puStack_198;
  undefined8 *puStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  longlong lStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  longlong lStack_140;
  undefined8 *puStack_138;
  undefined8 *puStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  longlong lStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  longlong lStack_e0;
  undefined8 *puStack_d8;
  undefined8 *puStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  longlong lStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  longlong lStack_80;
  undefined8 *puStack_78;
  undefined8 *puStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  ulonglong uStack_58;
  
                    /* 0x2f72  3233
                       ?TofDataGrabber@DeviceStreamBlock@blocks@meta@@IEAAXPEBUDepthData@royale@@@Z
                        */
  uStack_240 = 0xfffffffffffffffe;
  uStack_58 = DAT_1802450f8 ^ (ulonglong)auStack_338;
  _Var13 = 0;
  uStack_318 = 0;
  uStack_b8 = _DAT_1800a1580;
  uStack_b0 = _UNK_1800a1588;
  lStack_a8 = 0;
  uStack_a0 = 0;
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  lStack_80 = 0;
  puStack_78 = &uStack_b0;
  puStack_70 = &uStack_68;
  uStack_60 = 0;
  uStack_68 = 0;
  uStack_2c0 = (uint)*(ushort *)(param_1 + 0x12);
  uStack_2bc = (uint)*(ushort *)(param_1 + 0x10);
  iVar14 = 2;
  apDStack_260[0] = param_1;
  apDStack_250[0] = this;
  cv::Mat::create((Mat *)&uStack_b8,2,(int *)&uStack_2c0,0x15);
  uStack_118 = _DAT_1800a1580;
  uStack_110 = _UNK_1800a1588;
  lStack_108 = 0;
  uStack_100 = 0;
  uStack_f8 = 0;
  uStack_f0 = 0;
  uStack_e8 = 0;
  lStack_e0 = 0;
  puStack_d8 = &uStack_110;
  puStack_d0 = &uStack_c8;
  uStack_c0 = 0;
  uStack_c8 = 0;
  uStack_2b8 = (uint)*(ushort *)(param_1 + 0x12);
  uStack_2b4 = (uint)*(ushort *)(param_1 + 0x10);
  cv::Mat::create((Mat *)&uStack_118,2,(int *)&uStack_2b8,0);
  uStack_178 = _DAT_1800a1580;
  uStack_170 = _UNK_1800a1588;
  lStack_168 = 0;
  uStack_160 = 0;
  uStack_158 = 0;
  uStack_150 = 0;
  uStack_148 = 0;
  lStack_140 = 0;
  puStack_138 = &uStack_170;
  puStack_130 = &uStack_128;
  uStack_120 = 0;
  uStack_128 = 0;
  uStack_2b0 = (uint)*(ushort *)(param_1 + 0x12);
  uStack_2ac = (uint)*(ushort *)(param_1 + 0x10);
  cv::Mat::create((Mat *)&uStack_178,2,(int *)&uStack_2b0,5);
  uStack_1d8 = _DAT_1800a1580;
  uStack_1d0 = _UNK_1800a1588;
  lStack_1c8 = 0;
  uStack_1c0 = 0;
  uStack_1b8 = 0;
  uStack_1b0 = 0;
  uStack_1a8 = 0;
  lStack_1a0 = 0;
  puStack_198 = &uStack_1d0;
  puStack_190 = &uStack_188;
  uStack_180 = 0;
  uStack_188 = 0;
  uStack_2a8 = (uint)*(ushort *)(param_1 + 0x12);
  uStack_2a4 = (uint)*(ushort *)(param_1 + 0x10);
  cv::Mat::create((Mat *)&uStack_1d8,2,(int *)&uStack_2a8,2);
  uStack_238 = _DAT_1800a1580;
  uStack_230 = _UNK_1800a1588;
  lStack_228 = 0;
  uStack_220 = 0;
  uStack_218 = 0;
  uStack_210 = 0;
  uStack_208 = 0;
  lStack_200 = 0;
  puStack_1f8 = &uStack_230;
  puStack_1f0 = &uStack_1e8;
  uStack_1e0 = 0;
  uStack_1e8 = 0;
  uStack_2a0 = (uint)*(ushort *)(param_1 + 0x12);
  uStack_29c = (uint)*(ushort *)(param_1 + 0x10);
  cv::Mat::create((Mat *)&uStack_238,2,(int *)&uStack_2a0,2);
  lVar12 = lStack_a8;
  lVar10 = lStack_108;
  alStack_298[0] = lStack_168;
  alStack_280[0] = lStack_1c8;
  alStack_270[0] = lStack_228;
  uVar15 = 0;
  this_00 = (Vector<royale::DepthPoint> *)(param_1 + 0x48);
  _Var8 = royale::Vector<royale::DepthPoint>::size(this_00);
  lVar11 = alStack_298[0];
  fVar6 = DAT_1800a1554;
  if (_Var8 != 0) {
    do {
      pDVar9 = royale::Vector<royale::DepthPoint>::operator[](this_00,_Var13);
      uVar3 = *(undefined4 *)(pDVar9 + 4);
      fVar4 = *(float *)(pDVar9 + 8);
      uVar5 = *(undefined4 *)(pDVar9 + 0xc);
      uStack_288 = *(undefined4 *)(pDVar9 + 0x10);
      *(undefined4 *)(lVar12 + (longlong)(iVar14 + -2) * 4) = *(undefined4 *)pDVar9;
      *(undefined4 *)(lVar12 + (longlong)(iVar14 + -1) * 4) = uVar3;
      *(float *)(lVar12 + (longlong)iVar14 * 4) = fVar4;
      *(char *)(_Var13 + lVar10) = (char)((uint)uStack_288 >> 0x10);
      *(undefined4 *)(lVar11 + _Var13 * 4) = uVar5;
      *(undefined2 *)(alStack_280[0] + _Var13 * 2) = (undefined2)uStack_288;
      *(short *)(alStack_270[0] + _Var13 * 2) = (short)(int)(fVar4 * fVar6);
      uVar15 = uVar15 + 1;
      iVar14 = iVar14 + 3;
      _Var13 = (__uint64)uVar15;
      _Var8 = royale::Vector<royale::DepthPoint>::size(this_00);
    } while (_Var13 < _Var8);
    param_1 = apDStack_260[0];
  }
  lVar10 = _Query_perf_frequency();
  lVar11 = _Query_perf_counter();
  lVar12 = (lVar11 % lVar10) * 1000000000;
  lVar11 = (lVar11 / lVar10) * 1000000000 + lVar12 / lVar10;
  dVar16 = device::RoyaleTimestampToSeconds(*(undefined8 *)(param_1 + 8),lVar12 % lVar10);
  std::make_shared<types::ImageFrame>();
  uStack_318 = 1;
  cv::Mat::operator=((Mat *)(puStack_2d0 + 0xb),(Mat *)&uStack_b8);
  pDVar7 = apDStack_250[0];
  *puStack_2d0 = *(undefined8 *)(apDStack_250[0] + 0x8e8);
  puStack_2d0[1] = dVar16;
  std::
  unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
  ::
  _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
            ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
              *)(puStack_2d0 + 2),
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)apDStack_250);
  *(longlong *)(apDStack_250[0] + 0x30) = lVar11;
  puStack_2d0[10] = *(undefined8 *)(param_1 + 0x78);
  (**(code **)(**(longlong **)(pDVar7 + 0x3f0) + 8))(*(longlong **)(pDVar7 + 0x3f0),&puStack_2d0);
  std::make_shared<types::ImageFrame>();
  uStack_318 = 3;
  cv::Mat::operator=((Mat *)(puStack_2e0 + 0xb),(Mat *)&uStack_1d8);
  *puStack_2e0 = *(undefined8 *)(pDVar7 + 0x8e8);
  puStack_2e0[1] = dVar16;
  std::
  unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
  ::
  _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
            ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
              *)(puStack_2e0 + 2),
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)apDStack_260);
  *(longlong *)(apDStack_260[0] + 0x30) = lVar11;
  puStack_2e0[10] = *(undefined8 *)(param_1 + 0x78);
  (**(code **)(**(longlong **)(pDVar7 + 0x528) + 8))(*(longlong **)(pDVar7 + 0x528),&puStack_2e0);
  std::make_shared<types::ImageFrame>();
  uStack_318 = 7;
  cv::Mat::operator=((Mat *)(puStack_2f0 + 0xb),(Mat *)&uStack_178);
  *puStack_2f0 = *(undefined8 *)(pDVar7 + 0x8e8);
  puStack_2f0[1] = dVar16;
  std::
  unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
  ::
  _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
            ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
              *)(puStack_2f0 + 2),
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)alStack_270);
  *(longlong *)(alStack_270[0] + 0x30) = lVar11;
  puStack_2f0[10] = *(undefined8 *)(param_1 + 0x78);
  (**(code **)(**(longlong **)(pDVar7 + 0x458) + 8))(*(longlong **)(pDVar7 + 0x458),&puStack_2f0);
  std::make_shared<types::ImageFrame>();
  uStack_318 = 0xf;
  cv::Mat::operator=((Mat *)(puStack_300 + 0xb),(Mat *)&uStack_238);
  *puStack_300 = *(undefined8 *)(pDVar7 + 0x8e8);
  puStack_300[1] = dVar16;
  std::
  unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
  ::
  _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
            ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
              *)(puStack_300 + 2),
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)alStack_280);
  *(longlong *)(alStack_280[0] + 0x30) = lVar11;
  puStack_300[10] = *(undefined8 *)(param_1 + 0x78);
  (**(code **)(**(longlong **)(pDVar7 + 0x590) + 8))(*(longlong **)(pDVar7 + 0x590),&puStack_300);
  std::make_shared<types::ImageFrame>();
  uStack_318 = 0x1f;
  cv::Mat::operator=((Mat *)(puStack_310 + 0xb),(Mat *)&uStack_118);
  *puStack_310 = *(undefined8 *)(pDVar7 + 0x8e8);
  puStack_310[1] = dVar16;
  std::
  unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
  ::
  _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
            ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
              *)(puStack_310 + 2),
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)alStack_298);
  *(longlong *)(alStack_298[0] + 0x30) = lVar11;
  puStack_310[10] = *(undefined8 *)(param_1 + 0x78);
  (**(code **)(**(longlong **)(pDVar7 + 0x4c0) + 8))(*(longlong **)(pDVar7 + 0x4c0),&puStack_310);
  *(longlong *)(pDVar7 + 0x8e8) = *(longlong *)(pDVar7 + 0x8e8) + 1;
  if (plStack_308 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_308 + 1;
    lVar11 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar11 == 1) {
      (**(code **)*plStack_308)(plStack_308);
      LOCK();
      piVar2 = (int *)((longlong)plStack_308 + 0xc);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 == 1) {
        (**(code **)(*plStack_308 + 8))(plStack_308);
      }
    }
  }
  if (plStack_2f8 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_2f8 + 1;
    lVar11 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar11 == 1) {
      (**(code **)*plStack_2f8)(plStack_2f8);
      LOCK();
      piVar2 = (int *)((longlong)plStack_2f8 + 0xc);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 == 1) {
        (**(code **)(*plStack_2f8 + 8))(plStack_2f8);
      }
    }
  }
  if (plStack_2e8 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_2e8 + 1;
    lVar11 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar11 == 1) {
      (**(code **)*plStack_2e8)(plStack_2e8);
      LOCK();
      piVar2 = (int *)((longlong)plStack_2e8 + 0xc);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 == 1) {
        (**(code **)(*plStack_2e8 + 8))(plStack_2e8);
      }
    }
  }
  if (plStack_2d8 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_2d8 + 1;
    lVar11 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar11 == 1) {
      (**(code **)*plStack_2d8)(plStack_2d8);
      LOCK();
      piVar2 = (int *)((longlong)plStack_2d8 + 0xc);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 == 1) {
        (**(code **)(*plStack_2d8 + 8))(plStack_2d8);
      }
    }
  }
  if (plStack_2c8 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_2c8 + 1;
    lVar11 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar11 == 1) {
      (**(code **)*plStack_2c8)(plStack_2c8);
      LOCK();
      piVar2 = (int *)((longlong)plStack_2c8 + 0xc);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 == 1) {
        (**(code **)(*plStack_2c8 + 8))(plStack_2c8);
      }
    }
  }
  if (lStack_200 != 0) {
    LOCK();
    piVar2 = (int *)(lStack_200 + 0x14);
    iVar14 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar14 == 1) {
      cv::Mat::deallocate((Mat *)&uStack_238);
    }
  }
  lStack_200 = 0;
  lStack_228 = 0;
  uStack_210 = 0;
  uStack_218 = 0;
  uStack_220 = 0;
  iVar14 = 0;
  if (0 < uStack_238._4_4_) {
    lVar11 = 0;
    do {
      *(undefined4 *)((longlong)puStack_1f8 + lVar11) = 0;
      iVar14 = iVar14 + 1;
      lVar11 = lVar11 + 4;
    } while (iVar14 < uStack_238._4_4_);
  }
  if (puStack_1f0 != &uStack_1e8) {
    cv::fastFree(puStack_1f0);
  }
  if (lStack_1a0 != 0) {
    LOCK();
    piVar2 = (int *)(lStack_1a0 + 0x14);
    iVar14 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar14 == 1) {
      cv::Mat::deallocate((Mat *)&uStack_1d8);
    }
  }
  lStack_1a0 = 0;
  lStack_1c8 = 0;
  uStack_1b0 = 0;
  uStack_1b8 = 0;
  uStack_1c0 = 0;
  iVar14 = 0;
  if (0 < uStack_1d8._4_4_) {
    lVar11 = 0;
    do {
      *(undefined4 *)((longlong)puStack_198 + lVar11) = 0;
      iVar14 = iVar14 + 1;
      lVar11 = lVar11 + 4;
    } while (iVar14 < uStack_1d8._4_4_);
  }
  if (puStack_190 != &uStack_188) {
    cv::fastFree(puStack_190);
  }
  if (lStack_140 != 0) {
    LOCK();
    piVar2 = (int *)(lStack_140 + 0x14);
    iVar14 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar14 == 1) {
      cv::Mat::deallocate((Mat *)&uStack_178);
    }
  }
  lStack_140 = 0;
  lStack_168 = 0;
  uStack_150 = 0;
  uStack_158 = 0;
  uStack_160 = 0;
  iVar14 = 0;
  if (0 < uStack_178._4_4_) {
    lVar11 = 0;
    do {
      *(undefined4 *)((longlong)puStack_138 + lVar11) = 0;
      iVar14 = iVar14 + 1;
      lVar11 = lVar11 + 4;
    } while (iVar14 < uStack_178._4_4_);
  }
  if (puStack_130 != &uStack_128) {
    cv::fastFree(puStack_130);
  }
  if (lStack_e0 != 0) {
    LOCK();
    piVar2 = (int *)(lStack_e0 + 0x14);
    iVar14 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar14 == 1) {
      cv::Mat::deallocate((Mat *)&uStack_118);
    }
  }
  lStack_e0 = 0;
  lStack_108 = 0;
  uStack_f0 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  iVar14 = 0;
  if (0 < uStack_118._4_4_) {
    lVar11 = 0;
    do {
      *(undefined4 *)((longlong)puStack_d8 + lVar11) = 0;
      iVar14 = iVar14 + 1;
      lVar11 = lVar11 + 4;
    } while (iVar14 < uStack_118._4_4_);
  }
  if (puStack_d0 != &uStack_c8) {
    cv::fastFree(puStack_d0);
  }
  if (lStack_80 != 0) {
    LOCK();
    piVar2 = (int *)(lStack_80 + 0x14);
    iVar14 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar14 == 1) {
      cv::Mat::deallocate((Mat *)&uStack_b8);
    }
  }
  lStack_80 = 0;
  lStack_a8 = 0;
  uStack_90 = 0;
  uStack_98 = 0;
  uStack_a0 = 0;
  iVar14 = 0;
  if (0 < uStack_b8._4_4_) {
    lVar11 = 0;
    do {
      *(undefined4 *)((longlong)puStack_78 + lVar11) = 0;
      iVar14 = iVar14 + 1;
      lVar11 = lVar11 + 4;
    } while (iVar14 < uStack_b8._4_4_);
  }
  if (puStack_70 != &uStack_68) {
    cv::fastFree(puStack_70);
  }
  return;
}


/* ==================== destroy<std::_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64>*___ptr64> @ 180003026  (5 bytes) ==================== */

/* public: static void __cdecl std::_Default_allocator_traits<class std::allocator<struct
   std::_Tree_node<struct std::pair<unsigned int const ,struct sdc::TofConfig>,void * __ptr64> >
   >::destroy<struct std::_Tree_node<struct std::pair<unsigned int const ,struct
   sdc::TofConfig>,void * __ptr64> * __ptr64>(class std::allocator<struct std::_Tree_node<struct
   std::pair<unsigned int const ,struct sdc::TofConfig>,void * __ptr64> > & __ptr64,struct
   std::_Tree_node<struct std::pair<unsigned int const ,struct sdc::TofConfig>,void * __ptr64> *
   __ptr64 * __ptr64 const) */

void __cdecl
std::
_Default_allocator_traits<std::allocator<std::_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64>_>_>
::destroy<std::_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64>*___ptr64>
          (allocator<std::_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64>_>
           *param_1,
          _Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> **param_2)

{
                    /* 0x3026  956
                       ??$destroy@PEAU?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@std@@@?$_Default_allocator_traits@V?$allocator@U?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@std@@@std@@@std@@SAXAEAV?$allocator@U?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@std@@@1@QEAPEAU?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@1@@Z
                        */
  return;
}


/* ==================== unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_> @ 18000310c  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::CircularBuffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> > > >::unique_ptr<class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> > > >(class
   coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64) __ptr64 */

unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
::
unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,CircularBuffer<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x310c  1890
                       ??0?$unique_ptr@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(CircularBuffer<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== forward<std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_> @ 18000313e  (5 bytes) ==================== */

/* struct std::default_delete<class coco::Data<class std::shared_ptr<struct types::ImageFrame> > >
   && __ptr64 __cdecl std::forward<struct std::default_delete<class coco::Data<class
   std::shared_ptr<struct types::ImageFrame> > > >(struct std::default_delete<class coco::Data<class
   std::shared_ptr<struct types::ImageFrame> > > & __ptr64) */

default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_> * __cdecl
std::forward<std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
          (default_delete<class_coco::Data<class_std::shared_ptr<struct_types::ImageFrame>_>_>
           *param_1)

{
                    /* 0x313e  1214
                       ??$forward@U?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@YA$$QEAU?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@0@AEAU10@@Z
                        */
  return (default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_> *)param_1;
}


/* ==================== make_unique<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,void> @ 180003175  (5 bytes) ==================== */

/* class std::unique_ptr<class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> > > > __cdecl std::make_unique<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> >,void>(void)
    */

void __cdecl
std::make_unique<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,void>
          (void)

{
  undefined8 *puVar1;
  undefined8 *in_RCX;
  
                    /* 0x3175  1326
                       ??$make_unique@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$$VX@std@@YA?AV?$unique_ptr@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@0@XZ
                        */
  puVar1 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar1 == (undefined8 *)0x0) {
    *in_RCX = 0;
    return;
  }
  puVar1[1] = 0;
  *(undefined1 *)(puVar1 + 1) = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  *puVar1 = coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
  puVar1[5] = 0;
  *in_RCX = puVar1;
  return;
}


/* ==================== _Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_> @ 180003184  (5 bytes) ==================== */

/* public: __cdecl std::_Deque_val<struct std::_Deque_simple_types<class std::shared_ptr<struct
   types::ImageFrame> > >::_Deque_val<struct std::_Deque_simple_types<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>::
_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>
          (_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_> *this)

{
                    /* 0x3184  1597
                       ??0?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  return this;
}


/* ==================== InitializeTof @ 18000318e  (5 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: bool __cdecl meta::blocks::DeviceStreamBlock::InitializeTof(void) __ptr64 */

bool __thiscall meta::blocks::DeviceStreamBlock::InitializeTof(DeviceStreamBlock *this)

{
  __uint64 *p_Var1;
  undefined8 uVar2;
  bool bVar3;
  int iVar4;
  char *pcVar5;
  LogMessage *pLVar6;
  basic_ostream<char,std::char_traits<char>_> *pbVar7;
  basicString<char> *pbVar8;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar9;
  Variant *pVVar10;
  Pair<royale::ProcessingFlag,royale::Variant> *pPVar11;
  undefined8 *puVar12;
  code *pcVar13;
  undefined1 auStack_118 [32];
  basicString<char> abStack_f8 [48];
  Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_> aVStack_c8 [48];
  undefined8 uStack_98;
  code *apcStack_90 [2];
  DeviceStreamBlock *pDStack_80;
  ulonglong uStack_78;
  ProcessingFlag PStack_70;
  undefined4 uStack_6c;
  hardware_error ahStack_50 [56];
  ulonglong uStack_18;
  
                    /* 0x318e  3111  ?InitializeTof@DeviceStreamBlock@blocks@meta@@IEAA_NXZ */
  uStack_98 = 0xfffffffffffffffe;
  uStack_18 = DAT_1802450f8 ^ (ulonglong)auStack_118;
  if (*(longlong **)(this + 0x8c8) == (longlong *)0x0) {
    pcVar5 = (char *)FUN_180043dd0(apcStack_90);
    pLVar6 = (LogMessage *)
             google::LogMessage::LogMessage
                       ((LogMessage *)&PStack_70,
                        "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                        ,0x18b,2);
    pbVar7 = google::LogMessage::stream(pLVar6);
    p_Var1 = (__uint64 *)(pcVar5 + 0x10);
    if (0xf < *(ulonglong *)(pcVar5 + 0x18)) {
      pcVar5 = *(char **)pcVar5;
    }
    pbVar7 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                       ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,pcVar5,*p_Var1)
    ;
    std::operator<<<std::char_traits<char>_>
              ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,
               "Failed to create ToF camera device");
    google::LogMessage::~LogMessage((LogMessage *)&PStack_70);
    if (0xf < uStack_78) {
      pcVar13 = apcStack_90[0];
      if ((0xfff < uStack_78 + 1) &&
         (((((ulonglong)apcStack_90[0] & 0x1f) != 0 ||
           (pcVar13 = *(code **)(apcStack_90[0] + -8), apcStack_90[0] <= pcVar13)) ||
          ((code *)0x1f < apcStack_90[0] + (-8 - (longlong)pcVar13))))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_180002658(pcVar13);
    }
    bVar3 = false;
  }
  else {
    iVar4 = (**(code **)(**(longlong **)(this + 0x8c8) + 0x10))();
    if (iVar4 != 0) {
      pbVar8 = (basicString<char> *)royale::getErrorString((CameraStatus)abStack_f8);
      pcVar5 = royale::basicString<char>::c_str(pbVar8);
      std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
      basic_string<char,std::char_traits<char>,std::allocator<char>_>
                ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)apcStack_90,
                 pcVar5);
      royale::basicString<char>::~basicString<char>(abStack_f8);
      pbVar9 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
               std::operator+<char,std::char_traits<char>,std::allocator<char>_>
                         ((char *)&PStack_70,
                          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)"Cannot initialize the camera device error code: ");
      fou::except::hardware_error::hardware_error(ahStack_50,pbVar9);
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(ahStack_50,(ThrowInfo *)&DAT_1800c4050);
    }
    royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
    Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(aVStack_c8);
    PStack_70 = 0xd;
    pVVar10 = (Variant *)royale::Variant::Variant((Variant *)apcStack_90,(bool)this[0xb38]);
    pPVar11 = (Pair<royale::ProcessingFlag,royale::Variant> *)
              royale::Pair<royale::ProcessingFlag,royale::Variant>::
              Pair<royale::ProcessingFlag,royale::Variant>
                        ((Pair<royale::ProcessingFlag,royale::Variant> *)abStack_f8,&PStack_70,
                         pVVar10);
    royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::push_back
              (aVStack_c8,pPVar11);
    royale::Pair<royale::ProcessingFlag,royale::Variant>::
    ~Pair<royale::ProcessingFlag,royale::Variant>
              ((Pair<royale::ProcessingFlag,royale::Variant> *)abStack_f8);
    royale::Variant::~Variant((Variant *)apcStack_90);
    PStack_70 = 0xf;
    pVVar10 = (Variant *)royale::Variant::Variant((Variant *)apcStack_90,(bool)this[0xb38]);
    pPVar11 = (Pair<royale::ProcessingFlag,royale::Variant> *)
              royale::Pair<royale::ProcessingFlag,royale::Variant>::
              Pair<royale::ProcessingFlag,royale::Variant>
                        ((Pair<royale::ProcessingFlag,royale::Variant> *)abStack_f8,&PStack_70,
                         pVVar10);
    royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::push_back
              (aVStack_c8,pPVar11);
    royale::Pair<royale::ProcessingFlag,royale::Variant>::
    ~Pair<royale::ProcessingFlag,royale::Variant>
              ((Pair<royale::ProcessingFlag,royale::Variant> *)abStack_f8);
    royale::Variant::~Variant((Variant *)apcStack_90);
    iVar4 = (**(code **)(**(longlong **)(this + 0x8c8) + 0x1c8))
                      (*(longlong **)(this + 0x8c8),aVStack_c8);
    if (iVar4 == 0) {
      apcStack_90[0] = TofDataGrabber;
      pDStack_80 = this;
      puVar12 = (undefined8 *)
                std::
                make_unique<RoyaleDataListener,std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void>
                          ((_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
                            *)&PStack_70);
      uVar2 = *puVar12;
      *puVar12 = 0;
      puVar12 = *(undefined8 **)(this + 0x8d0);
      *(undefined8 *)(this + 0x8d0) = uVar2;
      if (puVar12 != (undefined8 *)0x0) {
        (**(code **)*puVar12)(puVar12,1);
      }
      puVar12 = (undefined8 *)CONCAT44(uStack_6c,PStack_70);
      if (puVar12 != (undefined8 *)0x0) {
        (**(code **)*puVar12)(puVar12,1);
      }
      iVar4 = (**(code **)(**(longlong **)(this + 0x8c8) + 0xa0))
                        (*(longlong **)(this + 0x8c8),*(undefined8 *)(this + 0x8d0));
      if (iVar4 == 0) {
        iVar4 = (**(code **)(**(longlong **)(this + 0x8c8) + 0xf0))();
        if (iVar4 == 0) {
          royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
          ~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(aVStack_c8);
          bVar3 = true;
        }
        else {
          pbVar8 = (basicString<char> *)royale::getErrorString((CameraStatus)abStack_f8);
          pcVar5 = (char *)FUN_180043dd0(apcStack_90);
          pLVar6 = (LogMessage *)
                   google::LogMessage::LogMessage
                             ((LogMessage *)&PStack_70,
                              "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                              ,0x1b6,2);
          pbVar7 = google::LogMessage::stream(pLVar6);
          p_Var1 = (__uint64 *)(pcVar5 + 0x10);
          if (0xf < *(ulonglong *)(pcVar5 + 0x18)) {
            pcVar5 = *(char **)pcVar5;
          }
          pbVar7 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                             ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,pcVar5,
                              *p_Var1);
          pbVar7 = std::operator<<<std::char_traits<char>_>
                             ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,
                              "Cannot start capture. ERROR: ");
          royale::operator<<<char>
                    ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,pbVar8);
          google::LogMessage::~LogMessage((LogMessage *)&PStack_70);
          if (0xf < uStack_78) {
            pcVar13 = apcStack_90[0];
            if ((0xfff < uStack_78 + 1) &&
               (((((ulonglong)apcStack_90[0] & 0x1f) != 0 ||
                 (pcVar13 = *(code **)(apcStack_90[0] + -8), apcStack_90[0] <= pcVar13)) ||
                ((code *)0x1f < apcStack_90[0] + (-8 - (longlong)pcVar13))))) {
                    /* WARNING: Subroutine does not return */
              _invalid_parameter_noinfo_noreturn();
            }
            FUN_180002658(pcVar13);
          }
          pDStack_80 = (DeviceStreamBlock *)_DAT_1800a15a0;
          uStack_78 = _UNK_1800a15a8;
          apcStack_90[0] = (code *)((ulonglong)apcStack_90[0] & 0xffffffffffffff00);
          royale::basicString<char>::~basicString<char>(abStack_f8);
          royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
          ~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(aVStack_c8);
          bVar3 = false;
        }
      }
      else {
        pbVar8 = (basicString<char> *)royale::getErrorString((CameraStatus)abStack_f8);
        pcVar5 = (char *)FUN_180043dd0(apcStack_90);
        pLVar6 = (LogMessage *)
                 google::LogMessage::LogMessage
                           ((LogMessage *)&PStack_70,
                            "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                            ,0x1af,2);
        pbVar7 = google::LogMessage::stream(pLVar6);
        p_Var1 = (__uint64 *)(pcVar5 + 0x10);
        if (0xf < *(ulonglong *)(pcVar5 + 0x18)) {
          pcVar5 = *(char **)pcVar5;
        }
        pbVar7 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                           ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,pcVar5,
                            *p_Var1);
        pbVar7 = std::operator<<<std::char_traits<char>_>
                           ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,
                            "Cant Register Data Listener. ERROR:  ");
        royale::operator<<<char>
                  ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,pbVar8);
        google::LogMessage::~LogMessage((LogMessage *)&PStack_70);
        if (0xf < uStack_78) {
          pcVar13 = apcStack_90[0];
          if ((0xfff < uStack_78 + 1) &&
             (((((ulonglong)apcStack_90[0] & 0x1f) != 0 ||
               (pcVar13 = *(code **)(apcStack_90[0] + -8), apcStack_90[0] <= pcVar13)) ||
              ((code *)0x1f < apcStack_90[0] + (-8 - (longlong)pcVar13))))) {
                    /* WARNING: Subroutine does not return */
            _invalid_parameter_noinfo_noreturn();
          }
          FUN_180002658(pcVar13);
        }
        pDStack_80 = (DeviceStreamBlock *)_DAT_1800a15a0;
        uStack_78 = _UNK_1800a15a8;
        apcStack_90[0] = (code *)((ulonglong)apcStack_90[0] & 0xffffffffffffff00);
        royale::basicString<char>::~basicString<char>(abStack_f8);
        royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
        ~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(aVStack_c8);
        bVar3 = false;
      }
    }
    else {
      pbVar8 = (basicString<char> *)royale::getErrorString((CameraStatus)abStack_f8);
      pcVar5 = (char *)FUN_180043dd0(apcStack_90);
      pLVar6 = (LogMessage *)
               google::LogMessage::LogMessage
                         ((LogMessage *)&PStack_70,
                          "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                          ,0x1a4,2);
      pbVar7 = google::LogMessage::stream(pLVar6);
      p_Var1 = (__uint64 *)(pcVar5 + 0x10);
      if (0xf < *(ulonglong *)(pcVar5 + 0x18)) {
        pcVar5 = *(char **)pcVar5;
      }
      pbVar7 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                         ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,pcVar5,
                          *p_Var1);
      pbVar7 = std::operator<<<std::char_traits<char>_>
                         ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,
                          "Bad Processing Parameters. ERROR: ");
      bVar3 = royale::basicString<char>::empty(pbVar8);
      if (!bVar3) {
        pcVar5 = royale::basicString<char>::c_str(pbVar8);
        std::operator<<<std::char_traits<char>_>
                  ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar7,pcVar5);
      }
      google::LogMessage::~LogMessage((LogMessage *)&PStack_70);
      if (0xf < uStack_78) {
        pcVar13 = apcStack_90[0];
        if ((0xfff < uStack_78 + 1) &&
           (((((ulonglong)apcStack_90[0] & 0x1f) != 0 ||
             (pcVar13 = *(code **)(apcStack_90[0] + -8), apcStack_90[0] <= pcVar13)) ||
            ((code *)0x1f < apcStack_90[0] + (-8 - (longlong)pcVar13))))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
        FUN_180002658(pcVar13);
      }
      pDStack_80 = (DeviceStreamBlock *)_DAT_1800a15a0;
      uStack_78 = _UNK_1800a15a8;
      apcStack_90[0] = (code *)((ulonglong)apcStack_90[0] & 0xffffffffffffff00);
      royale::basicString<char>::~basicString<char>(abStack_f8);
      royale::Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>::
      ~Vector<royale::Pair<royale::ProcessingFlag,royale::Variant>_>(aVStack_c8);
      bVar3 = false;
    }
  }
  return bVar3;
}


/* ==================== ~_Tree_comp_alloc<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_> @ 1800031ca  (5 bytes) ==================== */

/* public: __cdecl std::_Tree_comp_alloc<class std::_Tmap_traits<unsigned int,struct
   sdc::TofConfig,struct std::less<unsigned int>,class std::allocator<struct std::pair<unsigned int
   const ,struct sdc::TofConfig> >,0> >::~_Tree_comp_alloc<class std::_Tmap_traits<unsigned
   int,struct sdc::TofConfig,struct std::less<unsigned int>,class std::allocator<struct
   std::pair<unsigned int const ,struct sdc::TofConfig> >,0> >(void) __ptr64 */

void __thiscall
std::
_Tree_comp_alloc<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_>
::
~_Tree_comp_alloc<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_>
          (_Tree_comp_alloc<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_>
           *this)

{
                    /* 0x31ca  2215
                       ??1?$_Tree_comp_alloc@V?$_Tmap_traits@IUTofConfig@sdc@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUTofConfig@sdc@@@std@@@4@$0A@@std@@@std@@QEAA@XZ
                        */
  FUN_180002658(*(undefined8 *)this);
  return;
}


/* ==================== make_shared<types::ImageFrame> @ 18000320b  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> __cdecl std::make_shared<struct
   types::ImageFrame>(void) */

void __cdecl std::make_shared<types::ImageFrame>(void)

{
  _Ref_count_base *p_Var1;
  _Ptr_base<types::ImageFrame> *in_RCX;
  
                    /* 0x320b  1297
                       ??$make_shared@UImageFrame@types@@$$V@std@@YA?AV?$shared_ptr@UImageFrame@types@@@0@XZ
                        */
  p_Var1 = (_Ref_count_base *)thunk_FUN_180084ee4(200);
  if (p_Var1 == (_Ref_count_base *)0x0) {
    p_Var1 = (_Ref_count_base *)0x0;
  }
  else {
    *(undefined4 *)(p_Var1 + 8) = 1;
    *(undefined4 *)(p_Var1 + 0xc) = 1;
    *(undefined ***)p_Var1 = _Ref_count_obj<types::ImageFrame>::vftable;
    memset((ImageFrame *)(p_Var1 + 0x10),0,0xb8);
    types::ImageFrame::ImageFrame((ImageFrame *)(p_Var1 + 0x10));
  }
  *(undefined8 *)in_RCX = 0;
  *(undefined8 *)(in_RCX + 8) = 0;
  _Ptr_base<types::ImageFrame>::_Reset0(in_RCX,(ImageFrame *)(p_Var1 + 0x10),p_Var1);
  return;
}


/* ==================== _Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64> @ 1800032ab  (5 bytes) ==================== */

/* public: __cdecl std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64>::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> && __ptr64) __ptr64
    */

_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
* __thiscall
std::
_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
::
_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
           *this,_Binder<struct_std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(struct_royale::DepthData_const*___ptr64)___ptr64,class_meta::blocks::DeviceStreamBlock*___ptr64,struct_std::_Ph<1>_const&___ptr64>
                 *param_1)

{
                    /* 0x32ab  1547
                       ??0?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@QEAA@$$QEAV01@@Z
                        */
  *(undefined8 *)this = *(undefined8 *)param_1;
  this[8] = *(_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
              *)(param_1 + 8);
  *(undefined8 *)(this + 0x10) = *(undefined8 *)(param_1 + 0x10);
  return this;
}


/* ==================== _Ptr_base<types::ImageFrame> @ 180003323  (5 bytes) ==================== */

/* public: __cdecl std::_Ptr_base<struct types::ImageFrame>::_Ptr_base<struct
   types::ImageFrame>(void) __ptr64 */

_Ptr_base<types::ImageFrame> * __thiscall
std::_Ptr_base<types::ImageFrame>::_Ptr_base<types::ImageFrame>(_Ptr_base<types::ImageFrame> *this)

{
                    /* 0x3323  1649  ??0?$_Ptr_base@UImageFrame@types@@@std@@QEAA@XZ */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  return this;
}


/* ==================== shared_ptr<coco::ConnectionBase><coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>,void> @ 180003396  (5 bytes) ==================== */

/* public: __cdecl std::shared_ptr<class coco::ConnectionBase>::shared_ptr<class
   coco::ConnectionBase><class coco::ConnectionTyped<class std::shared_ptr<struct types::ImageFrame>
   >,void>(class std::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > > && __ptr64) __ptr64 */

shared_ptr<coco::ConnectionBase> * __thiscall
std::shared_ptr<coco::ConnectionBase>::
shared_ptr<coco::ConnectionBase><coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>,void>
          (shared_ptr<coco::ConnectionBase> *this,
          shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *param_1)

{
                    /* 0x3396  257
                       ??$?0V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@X@?$shared_ptr@VConnectionBase@coco@@@std@@QEAA@$$QEAV?$shared_ptr@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@1@@Z
                        */
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  return this;
}


/* ==================== Imu0FrameGrabber @ 1800034b3  (5 bytes) ==================== */

/* private: void __cdecl meta::blocks::DeviceStreamBlock::Imu0FrameGrabber(class
   std::shared_ptr<struct sdc::RawImuData> const & __ptr64) __ptr64 */

void __thiscall
meta::blocks::DeviceStreamBlock::Imu0FrameGrabber
          (DeviceStreamBlock *this,shared_ptr<sdc::RawImuData> *param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  MatrixStamped<short,3,1> *pMStack_60;
  longlong *plStack_58;
  MatrixStamped<short,3,1> *pMStack_50;
  longlong *plStack_48;
  
                    /* 0x34b3  3105
                       ?Imu0FrameGrabber@DeviceStreamBlock@blocks@meta@@AEAAXAEBV?$shared_ptr@URawImuData@sdc@@@std@@@Z
                        */
  plStack_58 = (longlong *)thunk_FUN_180084ee4(0x70);
  if (plStack_58 == (longlong *)0x0) {
    plStack_58 = (longlong *)0x0;
  }
  else {
    *(undefined4 *)(plStack_58 + 1) = 1;
    *(undefined4 *)((longlong)plStack_58 + 0xc) = 1;
    *plStack_58 = (longlong)std::_Ref_count_obj<types::MatrixStamped<short,3,1>_>::vftable;
    types::Header::Header((Header *)(plStack_58 + 2));
    *(undefined4 *)(plStack_58 + 0xd) = 0;
    *(undefined2 *)((longlong)plStack_58 + 0x6c) = 0;
  }
  pMStack_60 = (MatrixStamped<short,3,1> *)(plStack_58 + 2);
  plStack_48 = (longlong *)thunk_FUN_180084ee4(0x70);
  if (plStack_48 == (longlong *)0x0) {
    plStack_48 = (longlong *)0x0;
  }
  else {
    *(undefined4 *)(plStack_48 + 1) = 1;
    *(undefined4 *)((longlong)plStack_48 + 0xc) = 1;
    *plStack_48 = (longlong)std::_Ref_count_obj<types::MatrixStamped<short,3,1>_>::vftable;
    types::Header::Header((Header *)(plStack_48 + 2));
    *(undefined4 *)(plStack_48 + 0xd) = 0;
    *(undefined2 *)((longlong)plStack_48 + 0x6c) = 0;
  }
  pMStack_50 = (MatrixStamped<short,3,1> *)(plStack_48 + 2);
  CreateImuFrame(this,param_1,pMStack_60,pMStack_50);
  if (0.0 < *(double *)(pMStack_60 + 8)) {
    (**(code **)(**(longlong **)(this + 0x5f8) + 8))(*(longlong **)(this + 0x5f8),&pMStack_60);
  }
  if (0.0 < *(double *)(pMStack_50 + 8)) {
    (**(code **)(**(longlong **)(this + 0x660) + 8))(*(longlong **)(this + 0x660),&pMStack_50);
  }
  plVar5 = plStack_48;
  if (plStack_48 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_48 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_48)(plStack_48);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  plVar5 = plStack_58;
  if (plStack_58 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_58 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_58)(plStack_58);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}


/* ==================== _Resetp0<types::ImageFrame> @ 180003661  (5 bytes) ==================== */

/* public: void __cdecl std::shared_ptr<struct types::ImageFrame>::_Resetp0<struct
   types::ImageFrame>(struct types::ImageFrame * __ptr64,class std::_Ref_count_base * __ptr64)
   __ptr64 */

void __thiscall
std::shared_ptr<types::ImageFrame>::_Resetp0<types::ImageFrame>
          (shared_ptr<types::ImageFrame> *this,ImageFrame *param_1,_Ref_count_base *param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  
                    /* 0x3661  637
                       ??$_Resetp0@UImageFrame@types@@@?$shared_ptr@UImageFrame@types@@@std@@QEAAXPEAUImageFrame@types@@PEAV_Ref_count_base@1@@Z
                        */
  plVar4 = *(longlong **)(this + 8);
  if (plVar4 == (longlong *)0x0) {
    *(_Ref_count_base **)(this + 8) = param_2;
    *(ImageFrame **)this = param_1;
  }
  else {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
      *(_Ref_count_base **)(this + 8) = param_2;
      *(ImageFrame **)this = param_1;
    }
    else {
      *(_Ref_count_base **)(this + 8) = param_2;
      *(ImageFrame **)this = param_1;
    }
  }
  return;
}


/* ==================== _Compressed_pair<std::default_delete<royale::IDepthDataListener>,royale::IDepthDataListener*___ptr64,1><royale::IDepthDataListener*___ptr64&___ptr64> @ 18000370b  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class
   royale::IDepthDataListener>,class royale::IDepthDataListener *
   __ptr64,1>::_Compressed_pair<struct std::default_delete<class royale::IDepthDataListener>,class
   royale::IDepthDataListener * __ptr64,1><class royale::IDepthDataListener * __ptr64 &
   __ptr64>(struct std::_Zero_then_variadic_args_t,class royale::IDepthDataListener * __ptr64 &
   __ptr64) __ptr64 */

_Compressed_pair<std::default_delete<royale::IDepthDataListener>,royale::IDepthDataListener*___ptr64,1>
* __thiscall
std::
_Compressed_pair<std::default_delete<royale::IDepthDataListener>,royale::IDepthDataListener*___ptr64,1>
::
_Compressed_pair<std::default_delete<royale::IDepthDataListener>,royale::IDepthDataListener*___ptr64,1><royale::IDepthDataListener*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<royale::IDepthDataListener>,royale::IDepthDataListener*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x370b  76
                       ??$?0AEAPEAVIDepthDataListener@royale@@@?$_Compressed_pair@U?$default_delete@VIDepthDataListener@royale@@@std@@PEAVIDepthDataListener@royale@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAVIDepthDataListener@royale@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== addressof<std::_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64>*___ptr64> @ 180003751  (5 bytes) ==================== */

/* struct std::_Tree_node<struct std::pair<unsigned int const ,struct sdc::TofConfig>,void *
   __ptr64> * __ptr64 * __ptr64 __cdecl std::addressof<struct std::_Tree_node<struct
   std::pair<unsigned int const ,struct sdc::TofConfig>,void * __ptr64> * __ptr64>(struct
   std::_Tree_node<struct std::pair<unsigned int const ,struct sdc::TofConfig>,void * __ptr64> *
   __ptr64 & __ptr64) */

_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> ** __cdecl
std::
addressof<std::_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64>*___ptr64>
          (_Tree_node<struct_std::pair<unsigned_int_const_,struct_sdc::TofConfig>,void*___ptr64>
           **param_1)

{
                    /* 0x3751  816
                       ??$addressof@PEAU?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@std@@@std@@YAPEAPEAU?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@0@AEAPEAU10@@Z
                        */
  return (_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> **)param_1;
}


/* ==================== make_unique<coco::Data<std::shared_ptr<types::ImageFrame>_>,void> @ 1800037a1  (5 bytes) ==================== */

/* class std::unique_ptr<class coco::Data<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::Data<class std::shared_ptr<struct types::ImageFrame> > > >
   __cdecl std::make_unique<class coco::Data<class std::shared_ptr<struct types::ImageFrame>
   >,void>(void) */

void __cdecl std::make_unique<coco::Data<std::shared_ptr<types::ImageFrame>_>,void>(void)

{
  undefined8 *puVar1;
  undefined8 *in_RCX;
  
                    /* 0x37a1  1344
                       ??$make_unique@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$$VX@std@@YA?AV?$unique_ptr@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@0@XZ
                        */
  puVar1 = (undefined8 *)thunk_FUN_180084ee4(0x128);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = coco::BufferBase<std::shared_ptr<types::ImageFrame>_>::vftable;
    *(undefined4 *)(puVar1 + 1) = 0;
    *(undefined1 *)((longlong)puVar1 + 0xc) = 0;
    coco::ConnectionStatisticsBuilder::ConnectionStatisticsBuilder
              ((ConnectionStatisticsBuilder *)(puVar1 + 2));
    *puVar1 = coco::Data<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar1[0x23] = 0;
    puVar1[0x24] = 0;
    puVar1[7] = 1;
    puVar1[0x13] = 0x7ff0000000000000;
    puVar1[0x1b] = 0x7ff0000000000000;
    puVar1[0x1e] = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[0xe] = 0;
    puVar1[0xf] = 0;
    coco::ConnectionStatisticsBuilder::ResetProducerStats
              ((ConnectionStatisticsBuilder *)(puVar1 + 2));
    puVar1[0x10] = 0x7ff0000000000000;
  }
  *in_RCX = puVar1;
  return;
}


/* ==================== ~unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_> @ 1800037e2  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> > > >::~unique_ptr<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> > > >(void) __ptr64 */

void __thiscall
std::
unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
::
~unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x37e2  2337
                       ??1?$unique_ptr@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000180030ec0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== operator=<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>,void> @ 18000380f  (5 bytes) ==================== */

/* public: class std::unique_ptr<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> > > > & __ptr64 __cdecl std::unique_ptr<class
   coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > >
   >::operator=<class coco::Data<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::Data<class std::shared_ptr<struct types::ImageFrame> >
   >,void>(class std::unique_ptr<class coco::Data<class std::shared_ptr<struct types::ImageFrame>
   >,struct std::default_delete<class coco::Data<class std::shared_ptr<struct types::ImageFrame> > >
   > && __ptr64) __ptr64 */

unique_ptr<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>,struct_std::default_delete<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
::
operator=<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>,void>
          (unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
                 *param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
                    /* 0x380f  351
                       ??$?4V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@X@?$unique_ptr@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAAAEAV01@$$QEAV?$unique_ptr@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@1@@Z
                        */
  uVar1 = *(undefined8 *)param_1;
  *(undefined8 *)param_1 = 0;
  puVar2 = *(undefined8 **)this;
  *(undefined8 *)this = uVar1;
  if (puVar2 != (undefined8 *)0x0) {
    (**(code **)*puVar2)(puVar2,1);
  }
  return (unique_ptr<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>,struct_std::default_delete<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>_>_>
          *)this;
}


/* ==================== _Compressed_pair<std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>,coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180003850  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> > >,class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64,1>::_Compressed_pair<struct
   std::default_delete<class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >
   >,class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64,1><class
   coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64>(struct std::_Zero_then_variadic_args_t,class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64) __ptr64 */

_Compressed_pair<std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>,coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
* __thiscall
std::
_Compressed_pair<std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>,coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
::
_Compressed_pair<std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>,coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>,coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x3850  40
                       ??$?0AEAPEAV?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Compressed_pair@U?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@PEAV?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAV?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== AudioFrameGrabber @ 180003878  (5 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* private: void __cdecl meta::blocks::DeviceStreamBlock::AudioFrameGrabber(class
   std::shared_ptr<struct sdc::AudioData> const & __ptr64) __ptr64 */

void __thiscall
meta::blocks::DeviceStreamBlock::AudioFrameGrabber
          (DeviceStreamBlock *this,shared_ptr<sdc::AudioData> *param_1)

{
  Header *this_00;
  __uint64 *p_Var1;
  longlong *plVar2;
  int *piVar3;
  int iVar4;
  char cVar5;
  longlong *plVar6;
  __uint64 _Var7;
  longlong lVar8;
  longlong lVar9;
  char *pcVar10;
  LogMessage *this_01;
  basic_ostream<char,std::char_traits<char>_> *pbVar11;
  ulonglong uVar12;
  double dVar13;
  undefined1 auStack_a8 [32];
  __uint64 *p_Stack_88;
  longlong *plStack_80;
  Header *pHStack_78;
  longlong *aplStack_70 [2];
  undefined8 uStack_60;
  LogMessage aLStack_58 [16];
  ulonglong auStack_48 [3];
  ulonglong uStack_30;
  ulonglong uStack_28;
  
                    /* 0x3878  2949
                       ?AudioFrameGrabber@DeviceStreamBlock@blocks@meta@@AEAAXAEBV?$shared_ptr@UAudioData@sdc@@@std@@@Z
                        */
  uStack_60 = 0xfffffffffffffffe;
  uStack_28 = DAT_1802450f8 ^ (ulonglong)auStack_a8;
  plVar6 = (longlong *)thunk_FUN_180084ee4(0x170);
  aplStack_70[0] = plVar6;
  if (plVar6 == (longlong *)0x0) {
    plVar6 = (longlong *)0x0;
  }
  else {
    *(undefined4 *)(plVar6 + 1) = 1;
    *(undefined4 *)((longlong)plVar6 + 0xc) = 1;
    *plVar6 = (longlong)std::_Ref_count_obj<types::AudioData>::vftable;
    this_00 = (Header *)(plVar6 + 2);
    pHStack_78 = this_00;
    memset(this_00,0,0x160);
    types::Header::Header(this_00);
  }
  p_Stack_88 = (__uint64 *)(plVar6 + 2);
  plStack_80 = plVar6;
  dVar13 = device::Meta2TimestampToSeconds(*(undefined8 *)(*(longlong *)param_1 + 0x104));
  p_Var1 = p_Stack_88;
  plVar6[3] = (longlong)dVar13;
  _Var7 = device::Meta2FrameIdToUint64(*(undefined8 *)(*(longlong *)param_1 + 0x120));
  *p_Var1 = _Var7;
  lVar8 = _Query_perf_frequency();
  lVar9 = _Query_perf_counter();
  std::
  unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
  ::
  _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
            ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
              *)(p_Stack_88 + 2),
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)aplStack_70);
  aplStack_70[0][6] = ((lVar9 % lVar8) * 1000000000) / lVar8 + (lVar9 / lVar8) * 1000000000;
  pHStack_78 = (Header *)(p_Stack_88 + 0xc);
  memmove(pHStack_78,*(void **)param_1,
          (ulonglong)*(uint *)((longlong)*(void **)param_1 + 0x100) << 2);
  p_Stack_88[0xb] = (ulonglong)*(uint *)(*(longlong *)param_1 + 0x100);
  cVar5 = (**(code **)(**(longlong **)(this + 0x800) + 8))(*(longlong **)(this + 0x800),&p_Stack_88)
  ;
  if (cVar5 == '\0') {
    pcVar10 = (char *)FUN_180043dd0(auStack_48);
    this_01 = (LogMessage *)
              google::LogMessage::LogMessage
                        (aLStack_58,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x1da,2);
    pbVar11 = google::LogMessage::stream(this_01);
    p_Var1 = (__uint64 *)(pcVar10 + 0x10);
    if (0xf < *(ulonglong *)(pcVar10 + 0x18)) {
      pcVar10 = *(char **)pcVar10;
    }
    pbVar11 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar11,pcVar10,
                         *p_Var1);
    std::operator<<<std::char_traits<char>_>
              ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar11,
               "Failed to write audio to output port.\n");
    google::LogMessage::~LogMessage(aLStack_58);
    if (0xf < uStack_30) {
      uVar12 = auStack_48[0];
      if ((0xfff < uStack_30 + 1) &&
         ((((auStack_48[0] & 0x1f) != 0 ||
           (uVar12 = *(ulonglong *)(auStack_48[0] - 8), auStack_48[0] <= uVar12)) ||
          (0x1f < (auStack_48[0] - uVar12) - 8)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_180002658(uVar12);
    }
  }
  plVar6 = plStack_80;
  if (plStack_80 != (longlong *)0x0) {
    LOCK();
    plVar2 = plStack_80 + 1;
    lVar8 = *plVar2;
    *(int *)plVar2 = (int)*plVar2 + -1;
    UNLOCK();
    if ((int)lVar8 == 1) {
      (**(code **)*plStack_80)(plStack_80);
      LOCK();
      piVar3 = (int *)((longlong)plVar6 + 0xc);
      iVar4 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar4 == 1) {
        (**(code **)(*plVar6 + 8))(plVar6);
      }
    }
  }
  return;
}


/* ==================== _Test_callable<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_> @ 180003945  (5 bytes) ==================== */

/* bool __cdecl std::_Test_callable<class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> >(class
   std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64> const & __ptr64) */

bool __cdecl
std::
_Test_callable<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_>
          (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
           *param_1)

{
                    /* 0x3945  665
                       ??$_Test_callable@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@@std@@YA_NAEBV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@@Z
                        */
  return true;
}


/* ==================== move<std::tuple<royale::DepthData_const*___ptr64&&___ptr64>&___ptr64> @ 180003a53  (5 bytes) ==================== */

/* class std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> && __ptr64 __cdecl
   std::move<class std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> & __ptr64>(class
   std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> & __ptr64) */

tuple<royale::DepthData_const*___ptr64&&___ptr64> * __cdecl
std::move<std::tuple<royale::DepthData_const*___ptr64&&___ptr64>&___ptr64>
          (tuple<struct_royale::DepthData_const*___ptr64&&___ptr64> *param_1)

{
                    /* 0x3a53  1393
                       ??$move@AEAV?$tuple@$$QEAPEBUDepthData@royale@@@std@@@std@@YA$$QEAV?$tuple@$$QEAPEBUDepthData@royale@@@0@AEAV10@@Z
                        */
  return (tuple<royale::DepthData_const*___ptr64&&___ptr64> *)param_1;
}


/* ==================== InputPort<std::shared_ptr<types::ImageFrame>_> @ 180003a9e  (5 bytes) ==================== */

/* public: __cdecl coco::InputPort<class std::shared_ptr<struct types::ImageFrame>
   >::InputPort<class std::shared_ptr<struct types::ImageFrame> >(class coco::Task * __ptr64,class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &
   __ptr64,bool) __ptr64 */

InputPort<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::InputPort<std::shared_ptr<types::ImageFrame>_>::InputPort<std::shared_ptr<types::ImageFrame>_>
          (InputPort<std::shared_ptr<types::ImageFrame>_> *this,Task *param_1,
          basic_string<char,std::char_traits<char>,std::allocator<char>_> *param_2,bool param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
                    /* 0x3a9e  1493
                       ??0?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@PEAVTask@1@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z
                        */
  coco::PortBase::PortBase((PortBase *)this,param_1,param_2,0,param_3);
  *(undefined ***)this = vftable;
  puVar2 = (undefined8 *)thunk_FUN_180084ee4();
  if (puVar2 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    puVar2[1] = 0;
    *(undefined1 *)(puVar2 + 1) = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0;
    *puVar2 = ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar2[5] = 0;
  }
  puVar1 = *(undefined8 **)(this + 8);
  *(undefined8 **)(this + 8) = puVar2;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  *(undefined8 *)(this + 0x60) = *(undefined8 *)(this + 8);
  return this;
}


/* ==================== ~InputPort<std::shared_ptr<types::ImageFrame>_> @ 180003ad5  (5 bytes) ==================== */

/* public: virtual __cdecl coco::InputPort<class std::shared_ptr<struct types::ImageFrame>
   >::~InputPort<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::InputPort<std::shared_ptr<types::ImageFrame>_>::
~InputPort<std::shared_ptr<types::ImageFrame>_>
          (InputPort<std::shared_ptr<types::ImageFrame>_> *this)

{
  undefined8 *puVar1;
  
                    /* 0x3ad5  2086
                       ??1?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ */
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(this + 0x38));
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(this + 0x18));
  puVar1 = *(undefined8 **)(this + 8);
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000180071b61. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== destroy<std::pair<unsigned_int_const_,sdc::TofConfig>_> @ 180003b1b  (5 bytes) ==================== */

/* public: static void __cdecl std::_Default_allocator_traits<class std::allocator<struct
   std::_Tree_node<struct std::pair<unsigned int const ,struct sdc::TofConfig>,void * __ptr64> >
   >::destroy<struct std::pair<unsigned int const ,struct sdc::TofConfig> >(class
   std::allocator<struct std::_Tree_node<struct std::pair<unsigned int const ,struct
   sdc::TofConfig>,void * __ptr64> > & __ptr64,struct std::pair<unsigned int const ,struct
   sdc::TofConfig> * __ptr64 const) */

void __cdecl
std::
_Default_allocator_traits<std::allocator<std::_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64>_>_>
::destroy<std::pair<unsigned_int_const_,sdc::TofConfig>_>
          (allocator<std::_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64>_>
           *param_1,pair<unsigned_int_const_,sdc::TofConfig> *param_2)

{
                    /* 0x3b1b  978
                       ??$destroy@U?$pair@$$CBIUTofConfig@sdc@@@std@@@?$_Default_allocator_traits@V?$allocator@U?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@std@@@std@@@std@@SAXAEAV?$allocator@U?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@std@@@1@QEAU?$pair@$$CBIUTofConfig@sdc@@@1@@Z
                        */
  return;
}


/* ==================== _Ptr_base<types::ImageFrame> @ 180003b2a  (5 bytes) ==================== */

/* public: __cdecl std::_Ptr_base<struct types::ImageFrame>::_Ptr_base<struct
   types::ImageFrame>(class std::_Ptr_base<struct types::ImageFrame> && __ptr64) __ptr64 */

_Ptr_base<types::ImageFrame> * __thiscall
std::_Ptr_base<types::ImageFrame>::_Ptr_base<types::ImageFrame>
          (_Ptr_base<types::ImageFrame> *this,_Ptr_base<struct_types::ImageFrame> *param_1)

{
                    /* 0x3b2a  1648  ??0?$_Ptr_base@UImageFrame@types@@@std@@QEAA@$$QEAV01@@Z */
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  return this;
}


/* ==================== ~ConnectionTyped<std::shared_ptr<types::ImageFrame>_> @ 180003b84  (5 bytes) ==================== */

/* public: virtual __cdecl coco::ConnectionTyped<class std::shared_ptr<struct types::ImageFrame>
   >::~ConnectionTyped<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::
~ConnectionTyped<std::shared_ptr<types::ImageFrame>_>
          (ConnectionTyped<std::shared_ptr<types::ImageFrame>_> *this)

{
  undefined8 *puVar1;
  
                    /* 0x3b84  2075
                       ??1?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ */
  _Cnd_destroy_in_situ(this + 0x98);
  _Mtx_destroy_in_situ(this + 0x48);
  puVar1 = *(undefined8 **)(this + 0x40);
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  puVar1 = *(undefined8 **)(this + 0x38);
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00018002cc77. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== ~function<void___cdecl(royale::DepthData_const*___ptr64)> @ 180003bed  (5 bytes) ==================== */

/* public: __cdecl std::function<void __cdecl(struct royale::DepthData const *
   __ptr64)>::~function<void __cdecl(struct royale::DepthData const * __ptr64)>(void) __ptr64 */

void __thiscall
std::function<void___cdecl(royale::DepthData_const*___ptr64)>::
~function<void___cdecl(royale::DepthData_const*___ptr64)>
          (function<void___cdecl(royale::DepthData_const*___ptr64)> *this)

{
  function<void___cdecl(royale::DepthData_const*___ptr64)> *pfVar1;
  
                    /* 0x3bed  2257  ??1?$function@$$A6AXPEBUDepthData@royale@@@Z@std@@QEAA@XZ */
  pfVar1 = *(function<void___cdecl(royale::DepthData_const*___ptr64)> **)(this + 0x38);
  if (pfVar1 != (function<void___cdecl(royale::DepthData_const*___ptr64)> *)0x0) {
    (**(code **)(*(longlong *)pfVar1 + 0x20))(pfVar1,pfVar1 != this);
    *(undefined8 *)(this + 0x38) = 0;
  }
  return;
}


/* ==================== _Ptr_move_cat<std::shared_ptr<types::ImageFrame>,std::shared_ptr<struct_types::ImageFrame>_> @ 180003c4c  (5 bytes) ==================== */

/* struct std::_General_ptr_iterator_tag __cdecl std::_Ptr_move_cat<class std::shared_ptr<struct
   types::ImageFrame>,class std::shared_ptr<struct types::ImageFrame> >(class std::shared_ptr<struct
   types::ImageFrame> * __ptr64 const & __ptr64,class std::shared_ptr<struct types::ImageFrame> *
   __ptr64 const & __ptr64) */

undefined8 __cdecl
std::_Ptr_move_cat<std::shared_ptr<types::ImageFrame>,std::shared_ptr<struct_types::ImageFrame>_>
          (shared_ptr<types::ImageFrame> **param_1,shared_ptr<types::ImageFrame> **param_2)

{
                    /* 0x3c4c  585
                       ??$_Ptr_move_cat@V?$shared_ptr@UImageFrame@types@@@std@@V12@@std@@YA?AU_General_ptr_iterator_tag@0@AEBQEAV?$shared_ptr@UImageFrame@types@@@0@0@Z
                        */
  return 0;
}


/* ==================== ~unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_> @ 180003c8d  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class royale::ICameraDevice,struct std::default_delete<class
   royale::ICameraDevice> >::~unique_ptr<class royale::ICameraDevice,struct
   std::default_delete<class royale::ICameraDevice> >(void) __ptr64 */

void __thiscall
std::unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_>::
~unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_>
          (unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_> *this)

{
  undefined8 *puVar1;
  
                    /* 0x3c8d  2376
                       ??1?$unique_ptr@VICameraDevice@royale@@U?$default_delete@VICameraDevice@royale@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000180031260. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== ~unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_> @ 180003d00  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> > > >::~unique_ptr<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > > >(void) __ptr64 */

void __thiscall
std::
unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
::
~unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x3d00  2343
                       ??1?$unique_ptr@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000180030f60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== ~BufferBase<std::shared_ptr<types::ImageFrame>_> @ 180003d41  (5 bytes) ==================== */

/* public: virtual __cdecl coco::BufferBase<class std::shared_ptr<struct types::ImageFrame>
   >::~BufferBase<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::BufferBase<std::shared_ptr<types::ImageFrame>_>::
~BufferBase<std::shared_ptr<types::ImageFrame>_>
          (BufferBase<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x3d41  2029
                       ??1?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ */
  std::vector<unsigned___int64,std::allocator<unsigned___int64>_>::_Tidy
            ((vector<unsigned___int64,std::allocator<unsigned___int64>_> *)(this + 0x100));
  std::
  deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
  ::
  ~deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
            ((deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
              *)(this + 0x10));
  return;
}


/* ==================== Data_RegisterNewAltFrame @ 180003d73  (5 bytes) ==================== */

/* public: virtual enum sdc::EventHandlerStatus __cdecl
   sdc::EventHandlerAdapter::Data_RegisterNewAltFrame(class std::function<void __cdecl(class
   std::shared_ptr<struct sdc::ImageData> const & __ptr64)>) __ptr64 */

EventHandlerStatus __thiscall
sdc::EventHandlerAdapter::Data_RegisterNewAltFrame(undefined8 param_1,longlong *param_2)

{
  longlong *plVar1;
  
                    /* 0x3d73  3030
                       ?Data_RegisterNewAltFrame@EventHandlerAdapter@sdc@@UEAA?AW4EventHandlerStatus@2@V?$function@$$A6AXAEBV?$shared_ptr@UImageData@sdc@@@std@@@Z@std@@@Z
                        */
  plVar1 = (longlong *)param_2[7];
  if (plVar1 != (longlong *)0x0) {
    (**(code **)(*plVar1 + 0x20))(plVar1,plVar1 != param_2);
    param_2[7] = 0;
  }
  return 0;
}


/* ==================== move<std::shared_ptr<types::ImageFrame>&___ptr64> @ 180003e4f  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> && __ptr64 __cdecl std::move<class
   std::shared_ptr<struct types::ImageFrame> & __ptr64>(class std::shared_ptr<struct
   types::ImageFrame> & __ptr64) */

shared_ptr<types::ImageFrame> * __cdecl
std::move<std::shared_ptr<types::ImageFrame>&___ptr64>
          (shared_ptr<struct_types::ImageFrame> *param_1)

{
                    /* 0x3e4f  1384
                       ??$move@AEAV?$shared_ptr@UImageFrame@types@@@std@@@std@@YA$$QEAV?$shared_ptr@UImageFrame@types@@@0@AEAV10@@Z
                        */
  return (shared_ptr<types::ImageFrame> *)param_1;
}


/* ==================== ~RoyaleDataListener @ 180003ea9  (5 bytes) ==================== */

/* public: virtual __cdecl RoyaleDataListener::~RoyaleDataListener(void) __ptr64 */

void __thiscall RoyaleDataListener::~RoyaleDataListener(RoyaleDataListener *this)

{
  RoyaleDataListener *pRVar1;
  
                    /* 0x3ea9  2420  ??1RoyaleDataListener@@UEAA@XZ */
  pRVar1 = *(RoyaleDataListener **)(this + 0x40);
  if (pRVar1 != (RoyaleDataListener *)0x0) {
    (**(code **)(*(longlong *)pRVar1 + 0x20))(pRVar1,pRVar1 != this + 8);
    *(undefined8 *)(this + 0x40) = 0;
  }
  *(undefined ***)this = royale::IDepthDataListener::vftable;
  return;
}


/* ==================== operator=<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>,void> @ 180003f4e  (5 bytes) ==================== */

/* public: class std::unique_ptr<class coco::ConnectionManager,struct std::default_delete<class
   coco::ConnectionManager> > & __ptr64 __cdecl std::unique_ptr<class coco::ConnectionManager,struct
   std::default_delete<class coco::ConnectionManager> >::operator=<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> > >,void>(class std::unique_ptr<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> > > > && __ptr64) __ptr64 */

unique_ptr<class_coco::ConnectionManager,struct_std::default_delete<class_coco::ConnectionManager>_>
* __thiscall
std::unique_ptr<coco::ConnectionManager,std::default_delete<coco::ConnectionManager>_>::
operator=<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>,void>
          (unique_ptr<coco::ConnectionManager,std::default_delete<coco::ConnectionManager>_> *this,
          unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
          *param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
                    /* 0x3f4e  333
                       ??$?4V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@X@?$unique_ptr@VConnectionManager@coco@@U?$default_delete@VConnectionManager@coco@@@std@@@std@@QEAAAEAV01@$$QEAV?$unique_ptr@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@1@@Z
                        */
  uVar1 = *(undefined8 *)param_1;
  *(undefined8 *)param_1 = 0;
  puVar2 = *(undefined8 **)this;
  *(undefined8 *)this = uVar1;
  if (puVar2 != (undefined8 *)0x0) {
    (**(code **)*puVar2)(puVar2,1);
  }
  return (unique_ptr<class_coco::ConnectionManager,struct_std::default_delete<class_coco::ConnectionManager>_>
          *)this;
}


/* ==================== _Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>,1><> @ 180003fe4  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> >,class std::_Deque_val<struct std::_Deque_simple_types<class
   std::shared_ptr<struct types::ImageFrame> > >,1>::_Compressed_pair<class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> >,class std::_Deque_val<struct
   std::_Deque_simple_types<class std::shared_ptr<struct types::ImageFrame> > >,1><>(struct
   std::_Zero_then_variadic_args_t) __ptr64 */

_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>,1>
* __thiscall
std::
_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>,1>
::
_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>,1><>
          (_Compressed_pair<std::allocator<std::shared_ptr<types::ImageFrame>_>,std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>,1>
           *this)

{
                    /* 0x3fe4  8
                       ??$?0$$V@?$_Compressed_pair@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@std@@V?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@2@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@@Z
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  return this;
}


/* ==================== unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_> @ 180004002  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> > > >::unique_ptr<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> > > >(class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64) __ptr64 */

unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
::
unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,Buffer<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x4002  1878
                       ??0?$unique_ptr@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(Buffer<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== forward<coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64> @ 180004089  (5 bytes) ==================== */

/* class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 && __ptr64
   __cdecl std::forward<class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64>(class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64) */

InputPort<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::forward<coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64>
          (InputPort<class_std::shared_ptr<struct_types::ImageFrame>_> **param_1)

{
                    /* 0x4089  1171
                       ??$forward@PEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YA$$QEAPEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (InputPort<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== _Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> @ 180004115  (5 bytes) ==================== */

/* public: __cdecl std::_Ptr_base<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >::_Ptr_base<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >(class std::_Ptr_base<class coco::ConnectionTyped<class
   std::shared_ptr<struct types::ImageFrame> > > && __ptr64) __ptr64 */

_Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::_Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
_Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
          (_Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *this,
          _Ptr_base<class_coco::ConnectionTyped<class_std::shared_ptr<struct_types::ImageFrame>_>_>
          *param_1)

{
                    /* 0x4115  1658
                       ??0?$_Ptr_base@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@$$QEAV01@@Z
                        */
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  return this;
}


/* ==================== ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_> @ 180004174  (5 bytes) ==================== */

/* public: __cdecl coco::ConnectionManagerInput<class std::shared_ptr<struct types::ImageFrame>
   >::ConnectionManagerInput<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_>::
ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x4174  1442
                       ??0?$ConnectionManagerInput@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@XZ
                        */
  this[8] = (ConnectionManagerInput<std::shared_ptr<types::ImageFrame>_>)0x0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined ***)this = vftable;
  return this;
}


/* ==================== RoyaleDataListener @ 1800042af  (5 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* public: __cdecl RoyaleDataListener::RoyaleDataListener(class std::function<void __cdecl(struct
   royale::DepthData const * __ptr64)>) __ptr64 */

RoyaleDataListener * __thiscall
RoyaleDataListener::RoyaleDataListener(RoyaleDataListener *this,longlong *param_2)

{
  _Func_class<void,struct_royale::DepthData_const*___ptr64> *this_00;
  undefined8 *puVar1;
  _Func_class<void,struct_royale::DepthData_const*___ptr64> *p_Var2;
  longlong *plVar3;
  undefined1 auStack_e8 [32];
  undefined8 uStack_c8;
  RoyaleDataListener *pRStack_c0;
  longlong *plStack_b8;
  _Func_class<void,struct_royale::DepthData_const*___ptr64> a_Stack_a8 [56];
  _Func_class<void,struct_royale::DepthData_const*___ptr64> *p_Stack_70;
  _Func_class<void,struct_royale::DepthData_const*___ptr64> a_Stack_68 [56];
  _Func_class<void,struct_royale::DepthData_const*___ptr64> *p_Stack_30;
  ulonglong uStack_28;
  
                    /* 0x42af  1958
                       ??0RoyaleDataListener@@QEAA@V?$function@$$A6AXPEBUDepthData@royale@@@Z@std@@@Z
                        */
  uStack_c8 = 0xfffffffffffffffe;
  uStack_28 = DAT_1802450f8 ^ (ulonglong)auStack_e8;
  *(undefined ***)this = vftable;
  *(undefined8 *)(this + 0x40) = 0;
  this_00 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)(this + 8);
  p_Stack_70 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0;
  puVar1 = (undefined8 *)param_2[7];
  pRStack_c0 = this;
  plStack_b8 = param_2;
  if (puVar1 != (undefined8 *)0x0) {
    p_Stack_70 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)
                 (**(code **)*puVar1)(puVar1,a_Stack_a8);
  }
  if ((p_Stack_70 != a_Stack_a8) &&
     (p_Var2 = *(_Func_class<void,struct_royale::DepthData_const*___ptr64> **)(this + 0x40),
     p_Var2 != this_00)) {
    *(_Func_class<void,struct_royale::DepthData_const*___ptr64> **)(this + 0x40) = p_Stack_70;
    p_Stack_70 = p_Var2;
    goto LAB_18002b053;
  }
  p_Stack_30 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0;
  if (p_Stack_70 != (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0) {
    if (p_Stack_70 == a_Stack_a8) {
      p_Stack_30 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)
                   (**(code **)(*(longlong *)p_Stack_70 + 8))(p_Stack_70,a_Stack_68);
      if (p_Stack_70 == (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0)
      goto LAB_18002b010;
      (**(code **)(*(longlong *)p_Stack_70 + 0x20))
                (p_Stack_70,CONCAT71((int7)((ulonglong)a_Stack_a8 >> 8),p_Stack_70 != a_Stack_a8));
    }
    else {
      p_Stack_30 = p_Stack_70;
    }
    p_Stack_70 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0;
  }
LAB_18002b010:
  std::_Func_class<void,royale::DepthData_const*___ptr64>::_Reset_move
            ((_Func_class<void,royale::DepthData_const*___ptr64> *)a_Stack_a8,this_00);
  std::_Func_class<void,royale::DepthData_const*___ptr64>::_Reset_move
            ((_Func_class<void,royale::DepthData_const*___ptr64> *)this_00,a_Stack_68);
  if (p_Stack_30 != (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0) {
    (**(code **)(*(longlong *)p_Stack_30 + 0x20))
              (p_Stack_30,CONCAT71((int7)((ulonglong)a_Stack_68 >> 8),p_Stack_30 != a_Stack_68));
  }
LAB_18002b053:
  if (p_Stack_70 != (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0) {
    (**(code **)(*(longlong *)p_Stack_70 + 0x20))
              (p_Stack_70,CONCAT71((int7)((ulonglong)a_Stack_a8 >> 8),p_Stack_70 != a_Stack_a8));
  }
  plVar3 = (longlong *)param_2[7];
  if (plVar3 != (longlong *)0x0) {
    (**(code **)(*plVar3 + 0x20))(plVar3,plVar3 != param_2);
    param_2[7] = 0;
  }
  return this;
}


/* ==================== RegisterTof @ 180004318  (5 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* private: void __cdecl meta::blocks::DeviceStreamBlock::RegisterTof(void) __ptr64 */

void __thiscall meta::blocks::DeviceStreamBlock::RegisterTof(DeviceStreamBlock *this)

{
  __uint64 *p_Var1;
  DeviceStreamBlock *pDVar2;
  _Ref_count_base *p_Var3;
  SAQDriverManagerAdapterCls *pSVar4;
  undefined8 *puVar5;
  longlong *plVar6;
  ulonglong uVar7;
  bool bVar8;
  int iVar9;
  uint uVar10;
  __uint64 _Var11;
  char *pcVar12;
  LogMessage *pLVar13;
  basic_ostream<char,std::char_traits<char>_> *pbVar14;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> *pbVar15;
  DeviceStreamBlock *pDVar16;
  undefined8 uVar17;
  basicString<char> *pbVar18;
  ApplicationManager *pAVar19;
  longlong lVar20;
  longlong lVar21;
  ulonglong uVar22;
  DeviceStreamBlock *pDVar23;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar24;
  uint uVar25;
  undefined1 auStack_3c8 [32];
  undefined4 uStack_3a8;
  uint uStack_398;
  CameraManager aCStack_390 [8];
  undefined8 *puStack_388;
  undefined8 uStack_380;
  undefined8 uStack_378;
  undefined8 uStack_370;
  LogMessage aLStack_368 [16];
  LogMessage aLStack_358 [16];
  LogMessage aLStack_348 [16];
  LogMessage aLStack_338 [16];
  LogMessage aLStack_328 [16];
  Vector<royale::basicString<char>_> aVStack_318 [48];
  basicString<char> abStack_2e8 [48];
  basicString<char> abStack_2b8 [48];
  basicString<char> abStack_288 [48];
  basicString<char> abStack_258 [48];
  basicString<char> abStack_228 [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> bStack_1f8;
  undefined7 uStack_1f7;
  longlong lStack_1e8;
  ulonglong uStack_1e0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> bStack_1d8;
  undefined7 uStack_1d7;
  __uint64 _Stack_1c8;
  ulonglong uStack_1c0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> bStack_1b8;
  undefined7 uStack_1b7;
  longlong lStack_1a8;
  ulonglong uStack_1a0;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> bStack_198;
  undefined7 uStack_197;
  longlong lStack_188;
  ulonglong uStack_180;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> bStack_178;
  undefined7 uStack_177;
  longlong lStack_168;
  ulonglong uStack_160;
  byte bStack_158;
  undefined7 uStack_157;
  longlong lStack_148;
  ulonglong uStack_140;
  byte bStack_138;
  undefined7 uStack_137;
  longlong lStack_128;
  ulonglong uStack_120;
  ulonglong auStack_118 [3];
  ulonglong uStack_100;
  ulonglong auStack_f8 [3];
  ulonglong uStack_e0;
  ulonglong auStack_d8 [3];
  ulonglong uStack_c0;
  hardware_error ahStack_b8 [56];
  undefined1 auStack_80 [32];
  char acStack_60 [32];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_40 [32];
  ulonglong uStack_20;
  
                    /* 0x4318  3176  ?RegisterTof@DeviceStreamBlock@blocks@meta@@AEAAXXZ */
  uStack_370 = 0xfffffffffffffffe;
  uStack_20 = DAT_1802450f8 ^ (ulonglong)auStack_3c8;
  uStack_398 = 0;
  royale::basicString<char>::basicString<char>
            (abStack_2e8,"d79dab562f13ef8373e906d919aec323a2857388");
  royale::CameraManager::CameraManager(aCStack_390,abStack_2e8);
  royale::basicString<char>::~basicString<char>(abStack_2e8);
  uStack_380 = 0;
  uStack_378 = 0;
  p_Var3 = *(_Ref_count_base **)(this + 0x8e0);
  pSVar4 = *(SAQDriverManagerAdapterCls **)(this + 0x8d8);
  uVar25 = 0;
  if (p_Var3 != (_Ref_count_base *)0x0) {
    LOCK();
    *(int *)(p_Var3 + 8) = *(int *)(p_Var3 + 8) + 1;
    UNLOCK();
    uVar25 = uStack_398;
  }
  std::_Ptr_base<sdc::SAQDriverManagerAdapterCls>::_Reset0
            ((_Ptr_base<sdc::SAQDriverManagerAdapterCls> *)&uStack_380,pSVar4,p_Var3);
  royale::CameraManager::getConnectedCameraList(aCStack_390,aVStack_318,&uStack_380);
  _Var11 = royale::Vector<royale::basicString<char>_>::size(aVStack_318);
  if (_Var11 == 0) {
    pcVar12 = (char *)FUN_180043dd0(auStack_118);
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (aLStack_368,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x141,2);
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    std::operator<<<std::char_traits<char>_>
              ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
               "No depth camera detected.");
    google::LogMessage::~LogMessage(aLStack_368);
    if (0xf < uStack_100) {
      uVar22 = auStack_118[0];
      if ((0xfff < uStack_100 + 1) &&
         ((((auStack_118[0] & 0x1f) != 0 ||
           (uVar22 = *(ulonglong *)(auStack_118[0] - 8), auStack_118[0] <= uVar22)) ||
          (0x1f < (auStack_118[0] - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_180002658(uVar22);
    }
    royale::Vector<royale::basicString<char>_>::~Vector<royale::basicString<char>_>(aVStack_318);
    royale::CameraManager::~CameraManager(aCStack_390);
    return;
  }
  if (1 < _Var11) {
    std::to_string((__uint64)auStack_80);
    pcVar12 = (char *)std::operator+<char,std::char_traits<char>,std::allocator<char>_>
                                (acStack_60,
                                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  *)"Expected 1, detected ");
    pbVar15 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)
              std::operator+<char,std::char_traits<char>,std::allocator<char>_>(abStack_40,pcVar12);
    fou::except::hardware_error::hardware_error(ahStack_b8,pbVar15);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(ahStack_b8,(ThrowInfo *)&DAT_1800c4050);
  }
  royale::Vector<royale::basicString<char>_>::operator[](aVStack_318,0);
  pDVar16 = (DeviceStreamBlock *)
            royale::CameraManager::createCamera(aCStack_390,(basicString<char> *)&puStack_388);
  pDVar2 = this + 0x8c8;
  if (pDVar2 != pDVar16) {
    lVar20 = *(longlong *)pDVar16;
    *(longlong *)pDVar16 = 0;
    puVar5 = *(undefined8 **)pDVar2;
    *(longlong *)pDVar2 = lVar20;
    if (puVar5 != (undefined8 *)0x0) {
      (**(code **)*puVar5)(puVar5,1);
    }
  }
  if (puStack_388 != (undefined8 *)0x0) {
    (**(code **)*puStack_388)(puStack_388,1);
  }
  if (-1 < *(int *)FLAGS_v_exref) {
    pcVar12 = (char *)FUN_180043dd0(auStack_f8);
    uStack_398 = 1;
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (aLStack_358,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x14b);
    uVar25 = 3;
    uStack_398 = 3;
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    std::operator<<<std::char_traits<char>_>
              ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,"Tof Camera Detected.."
              );
  }
  if ((uVar25 & 2) != 0) {
    uVar25 = uVar25 & 0xfffffffd;
    google::LogMessage::~LogMessage(aLStack_358);
  }
  if (((uVar25 & 1) != 0) && (uVar25 = uVar25 & 0xfffffffe, 0xf < uStack_e0)) {
    uVar22 = auStack_f8[0];
    if ((0xfff < uStack_e0 + 1) &&
       ((((auStack_f8[0] & 0x1f) != 0 ||
         (uVar22 = *(ulonglong *)(auStack_f8[0] - 8), auStack_f8[0] <= uVar22)) ||
        (0x1f < (auStack_f8[0] - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  royale::Vector<royale::basicString<char>_>::~Vector<royale::basicString<char>_>(aVStack_318);
  royale::CameraManager::~CameraManager(aCStack_390);
  bVar8 = InitializeTof(this);
  if (!bVar8) {
    return;
  }
  plVar6 = *(longlong **)pDVar2;
  pDVar16 = this + 0x8f8;
  pDVar23 = pDVar16;
  if (0xf < *(ulonglong *)(this + 0x910)) {
    pDVar23 = *(DeviceStreamBlock **)pDVar16;
  }
  uVar17 = royale::basicString<char>::basicString<char>(abStack_288,(char *)pDVar23);
  iVar9 = (**(code **)(*plVar6 + 0x48))(plVar6,uVar17);
  royale::basicString<char>::~basicString<char>(abStack_288);
  if (iVar9 != 0) {
    pbVar18 = (basicString<char> *)royale::getErrorString((CameraStatus)abStack_258);
    pcVar12 = (char *)FUN_180043dd0(&bStack_158);
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (aLStack_348,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x157,2);
    if (0xf < *(ulonglong *)(this + 0x910)) {
      pDVar16 = *(DeviceStreamBlock **)pDVar16;
    }
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    pbVar14 = std::operator<<<std::char_traits<char>_>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
                         "Cant set use case ");
    pbVar14 = std::operator<<<std::char_traits<char>_>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
                         (char *)pDVar16);
    pbVar14 = std::operator<<<std::char_traits<char>_>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,". ERROR: ");
    royale::operator<<<char>((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pbVar18);
    google::LogMessage::~LogMessage(aLStack_348);
    if (0xf < uStack_140) {
      uVar7 = CONCAT71(uStack_157,bStack_158);
      uVar22 = uVar7;
      if ((0xfff < uStack_140 + 1) &&
         ((((bStack_158 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22)) ||
          (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_180002658(uVar22);
    }
    lStack_148 = _DAT_1800a15a0;
    uStack_140 = _UNK_1800a15a8;
    bStack_158 = 0;
    royale::basicString<char>::~basicString<char>(abStack_258);
    return;
  }
  iVar9 = (**(code **)(**(longlong **)pDVar2 + 0x70))
                    (*(longlong **)pDVar2,*(undefined4 *)(this + 0x8f0));
  if (iVar9 != 0) {
    pbVar18 = (basicString<char> *)royale::getErrorString((CameraStatus)abStack_228);
    pcVar12 = (char *)FUN_180043dd0(&bStack_138);
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (aLStack_338,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x15f,2);
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    pbVar14 = std::operator<<<std::char_traits<char>_>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
                         "Cant set exposure. ERROR: ");
    royale::operator<<<char>((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pbVar18);
    google::LogMessage::~LogMessage(aLStack_338);
    if (0xf < uStack_120) {
      uVar7 = CONCAT71(uStack_137,bStack_138);
      uVar22 = uVar7;
      if ((0xfff < uStack_120 + 1) &&
         ((((bStack_138 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22)) ||
          (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
      FUN_180002658(uVar22);
    }
    lStack_128 = _DAT_1800a15a0;
    uStack_120 = _UNK_1800a15a8;
    bStack_138 = 0;
    royale::basicString<char>::~basicString<char>(abStack_228);
    return;
  }
  if (this[0xd18] == (DeviceStreamBlock)0x0) {
    return;
  }
  _Stack_1c8 = 0;
  uStack_1c0 = 0xf;
  bStack_1d8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
  lStack_1e8 = _DAT_1800a15a0;
  uStack_1e0 = _UNK_1800a15a8;
  bStack_1f8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
  pbVar15 = (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(this + 0xdb8);
  fou::os::BreakFileNameAndExtension(pbVar15,&bStack_1d8,&bStack_1f8);
  pbVar24 = &bStack_1f8;
  if (0xf < uStack_1e0) {
    pbVar24 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              CONCAT71(uStack_1f7,bStack_1f8);
  }
  if (lStack_1e8 == 4) {
    lVar20 = 0;
    do {
      lVar21 = lVar20 + 1;
      if (pbVar24[lVar20] !=
          *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           (&DAT_18009f718 + lVar20)) {
        uVar10 = -(uint)((byte)pbVar24[lVar20] <
                        (byte)*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(&DAT_18009f718 + lVar20)) | 1;
        goto LAB_18004672d;
      }
      lVar20 = lVar21;
    } while (lVar21 != 4);
    uVar10 = 0;
LAB_18004672d:
    if (uVar10 == 0) goto LAB_1800468de;
  }
  if (0 < *(int *)FLAGS_v_exref) {
    pcVar12 = (char *)FUN_180043dd0(auStack_d8);
    uStack_398 = uVar25 | 4;
    pLVar13 = (LogMessage *)
              google::LogMessage::LogMessage
                        (aLStack_328,
                         "D:\\jenkins\\workspace\\SDK2_Release_2.7.0-PRODUCTION\\jupiter\\meta_core\\blocks\\device\\device_stream_block.cpp"
                         ,0x16c);
    uVar25 = uVar25 | 0xc;
    uStack_398 = uVar25;
    pbVar14 = google::LogMessage::stream(pLVar13);
    p_Var1 = (__uint64 *)(pcVar12 + 0x10);
    if (0xf < *(ulonglong *)(pcVar12 + 0x18)) {
      pcVar12 = *(char **)pcVar12;
    }
    pbVar14 = std::_Insert_string<char,std::char_traits<char>,unsigned___int64>
                        ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,pcVar12,
                         *p_Var1);
    std::operator<<<std::char_traits<char>_>
              ((basic_ostream<char,struct_std::char_traits<char>_> *)pbVar14,
               "royale_recording_filename_ extension should be .rrf");
  }
  if ((uVar25 & 8) != 0) {
    uVar25 = uVar25 & 0xfffffff7;
    google::LogMessage::~LogMessage(aLStack_328);
  }
  if (((uVar25 & 4) != 0) && (uVar25 = uVar25 & 0xfffffffb, 0xf < uStack_c0)) {
    uVar22 = auStack_d8[0];
    if ((0xfff < uStack_c0 + 1) &&
       ((((auStack_d8[0] & 0x1f) != 0 ||
         (uVar22 = *(ulonglong *)(auStack_d8[0] - 8), auStack_d8[0] <= uVar22)) ||
        (0x1f < (auStack_d8[0] - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  lStack_1a8 = _DAT_1800a15a0;
  uStack_1a0 = _UNK_1800a15a8;
  bStack_1b8 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  uStack_398 = uVar25 | 0x10;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::reserve
            (&bStack_1b8,_Stack_1c8 + 4);
  pbVar24 = &bStack_1d8;
  if (0xf < uStack_1c0) {
    pbVar24 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              CONCAT71(uStack_1d7,bStack_1d8);
  }
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::append
            (&bStack_1b8,(char *)pbVar24,_Stack_1c8);
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::append(&bStack_1b8,".rrf",4)
  ;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::operator=
            (pbVar15,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )&bStack_1b8);
  if (0xf < uStack_1a0) {
    uVar7 = CONCAT71(uStack_1b7,bStack_1b8);
    uVar22 = uVar7;
    if ((0xfff < uStack_1a0 + 1) &&
       (((((byte)bStack_1b8 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22))
        || (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
LAB_1800468de:
  pAVar19 = coco::ApplicationManager::Get();
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>
            (&bStack_198,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (pAVar19 + 0x180));
  FUN_180040120(&bStack_178,pbVar15,&bStack_198);
  if (0xf < uStack_180) {
    uVar7 = CONCAT71(uStack_197,bStack_198);
    uVar22 = uVar7;
    if ((0xfff < uStack_180 + 1) &&
       (((((byte)bStack_198 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22))
        || (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  lStack_188 = _DAT_1800a15a0;
  uStack_180 = _UNK_1800a15a8;
  bStack_198 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  royale::basicString<char>::basicString<char>(abStack_2b8,&bStack_178);
  uStack_3a8 = 0;
  (**(code **)(**(longlong **)pDVar2 + 0x168))(*(longlong **)pDVar2,abStack_2b8,0,0);
  royale::basicString<char>::~basicString<char>(abStack_2b8);
  if (0xf < uStack_160) {
    uVar7 = CONCAT71(uStack_177,bStack_178);
    uVar22 = uVar7;
    if ((0xfff < uStack_160 + 1) &&
       (((((byte)bStack_178 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22))
        || (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  lStack_168 = _DAT_1800a15a0;
  uStack_160 = _UNK_1800a15a8;
  bStack_178 = (basic_string<char,std::char_traits<char>,std::allocator<char>_>)0x0;
  if (0xf < uStack_1e0) {
    uVar7 = CONCAT71(uStack_1f7,bStack_1f8);
    uVar22 = uVar7;
    if ((0xfff < uStack_1e0 + 1) &&
       (((((byte)bStack_1f8 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22))
        || (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  lStack_1e8 = _DAT_1800a15a0;
  uStack_1e0 = _UNK_1800a15a8;
  bStack_1f8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
  if (0xf < uStack_1c0) {
    uVar7 = CONCAT71(uStack_1d7,bStack_1d8);
    uVar22 = uVar7;
    if ((0xfff < uStack_1c0 + 1) &&
       (((((byte)bStack_1d8 & 0x1f) != 0 || (uVar22 = *(ulonglong *)(uVar7 - 8), uVar7 <= uVar22))
        || (0x1f < (uVar7 - uVar22) - 8)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_180002658(uVar22);
  }
  return;
}


/* ==================== _Rechecked<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64*___ptr64> @ 180004340  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 & __ptr64 __cdecl
   std::_Rechecked<class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,class
   std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64>(class std::shared_ptr<struct
   types::ImageFrame> * __ptr64 * __ptr64 & __ptr64,class std::shared_ptr<struct types::ImageFrame>
   * __ptr64 * __ptr64) */

shared_ptr<types::ImageFrame> *** __cdecl
std::
_Rechecked<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64*___ptr64>
          (shared_ptr<struct_types::ImageFrame> ***param_1,
          shared_ptr<struct_types::ImageFrame> **param_2)

{
                    /* 0x4340  594
                       ??$_Rechecked@PEAPEAV?$shared_ptr@UImageFrame@types@@@std@@PEAPEAV12@@std@@YAAEAPEAPEAV?$shared_ptr@UImageFrame@types@@@0@AEAPEAPEAV10@PEAPEAV10@@Z
                        */
  *param_1 = param_2;
  return (shared_ptr<types::ImageFrame> ***)param_1;
}


/* ==================== _Unique_ptr_base<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_><coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64> @ 18000439f  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class coco::CircularBuffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> > > >::_Unique_ptr_base<class
   coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >
   > ><class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64>(class
   coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64) __ptr64 */

_Unique_ptr_base<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Unique_ptr_base<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Unique_ptr_base<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_><coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64>
          (_Unique_ptr_base<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,CircularBuffer<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x439f  159
                       ??$?0PEAV?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Unique_ptr_base@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(CircularBuffer<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== IDepthDataListener @ 18000444e  (5 bytes) ==================== */

/* public: __cdecl royale::IDepthDataListener::IDepthDataListener(void) __ptr64 */

IDepthDataListener * __thiscall
royale::IDepthDataListener::IDepthDataListener(IDepthDataListener *this)

{
                    /* 0x444e  1947  ??0IDepthDataListener@royale@@QEAA@XZ */
  *(undefined ***)this = vftable;
  return this;
}


/* ==================== ~ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_> @ 180004575  (5 bytes) ==================== */

/* public: virtual __cdecl coco::ConnectionManagerTyped<class std::shared_ptr<struct
   types::ImageFrame> >::~ConnectionManagerTyped<class std::shared_ptr<struct types::ImageFrame>
   >(void) __ptr64 */

void __thiscall
coco::ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_>::
~ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerTyped<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x4575  2069
                       ??1?$ConnectionManagerTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ
                        */
  std::
  vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
  ::_Tidy((vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
           *)(this + 0x10));
  return;
}


/* ==================== _Unchecked<std::shared_ptr<types::ImageFrame>*___ptr64> @ 1800045ca  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 __cdecl std::_Unchecked<class
   std::shared_ptr<struct types::ImageFrame> * __ptr64>(class std::shared_ptr<struct
   types::ImageFrame> * __ptr64) */

shared_ptr<types::ImageFrame> * __cdecl
std::_Unchecked<std::shared_ptr<types::ImageFrame>*___ptr64>
          (shared_ptr<struct_types::ImageFrame> *param_1)

{
                    /* 0x45ca  695
                       ??$_Unchecked@PEAV?$shared_ptr@UImageFrame@types@@@std@@@std@@YAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAV10@@Z
                        */
  return (shared_ptr<types::ImageFrame> *)param_1;
}


/* ==================== shared_ptr<types::ImageFrame> @ 1800045cf  (5 bytes) ==================== */

/* public: __cdecl std::shared_ptr<struct types::ImageFrame>::shared_ptr<struct
   types::ImageFrame>(void) __ptr64 */

shared_ptr<types::ImageFrame> * __thiscall
std::shared_ptr<types::ImageFrame>::shared_ptr<types::ImageFrame>
          (shared_ptr<types::ImageFrame> *this)

{
                    /* 0x45cf  1825  ??0?$shared_ptr@UImageFrame@types@@@std@@QEAA@XZ */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  return this;
}


/* ==================== pair<royale::ProcessingFlag,royale::Variant><royale::ProcessingFlag,float,void,0> @ 18000461f  (5 bytes) ==================== */

/* public: __cdecl std::pair<enum royale::ProcessingFlag,class royale::Variant>::pair<enum
   royale::ProcessingFlag,class royale::Variant><enum royale::ProcessingFlag,float,void,0>(enum
   royale::ProcessingFlag && __ptr64,float && __ptr64) __ptr64 */

pair<royale::ProcessingFlag,royale::Variant> * __thiscall
std::pair<royale::ProcessingFlag,royale::Variant>::
pair<royale::ProcessingFlag,royale::Variant><royale::ProcessingFlag,float,void,0>
          (pair<royale::ProcessingFlag,royale::Variant> *this,ProcessingFlag *param_1,float *param_2
          )

{
  float fVar1;
  float fVar2;
  
  fVar2 = DAT_1800a1574;
                    /* 0x461f  312
                       ??$?0W4ProcessingFlag@royale@@MX$0A@@?$pair@W4ProcessingFlag@royale@@VVariant@2@@std@@QEAA@$$QEAW4ProcessingFlag@royale@@$$QEAM@Z
                        */
  fVar1 = DAT_1800a1560;
  *(ProcessingFlag *)this = *param_1;
  royale::Variant::Variant((Variant *)(this + 4),*param_2,fVar2,fVar1);
  return this;
}


/* ==================== shared_ptr<types::ImageFrame> @ 18000466f  (5 bytes) ==================== */

/* public: __cdecl std::shared_ptr<struct types::ImageFrame>::shared_ptr<struct
   types::ImageFrame>(class std::shared_ptr<struct types::ImageFrame> const & __ptr64) __ptr64 */

shared_ptr<types::ImageFrame> * __thiscall
std::shared_ptr<types::ImageFrame>::shared_ptr<types::ImageFrame>
          (shared_ptr<types::ImageFrame> *this,shared_ptr<struct_types::ImageFrame> *param_1)

{
  _Ref_count_base *p_Var1;
  ImageFrame *pIVar2;
  
                    /* 0x466f  1824  ??0?$shared_ptr@UImageFrame@types@@@std@@QEAA@AEBV01@@Z */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  p_Var1 = *(_Ref_count_base **)(param_1 + 8);
  pIVar2 = *(ImageFrame **)param_1;
  if (p_Var1 != (_Ref_count_base *)0x0) {
    LOCK();
    *(int *)(p_Var1 + 8) = *(int *)(p_Var1 + 8) + 1;
    UNLOCK();
  }
  _Ptr_base<types::ImageFrame>::_Reset0((_Ptr_base<types::ImageFrame> *)this,pIVar2,p_Var1);
  return this;
}


/* ==================== ~map<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>_> @ 1800046a6  (5 bytes) ==================== */

/* public: __cdecl std::map<unsigned int,struct sdc::TofConfig,struct std::less<unsigned int>,class
   std::allocator<struct std::pair<unsigned int const ,struct sdc::TofConfig> > >::~map<unsigned
   int,struct sdc::TofConfig,struct std::less<unsigned int>,class std::allocator<struct
   std::pair<unsigned int const ,struct sdc::TofConfig> > >(void) __ptr64 */

void __thiscall
std::
map<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>
::
~map<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>
          (map<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>
           *this)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
                    /* 0x46a6  2276
                       ??1?$map@IUTofConfig@sdc@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUTofConfig@sdc@@@std@@@4@@std@@QEAA@XZ
                        */
  cVar1 = *(char *)((longlong)*(longlong **)(*(longlong *)this + 8) + 0x19);
  plVar3 = *(longlong **)(*(longlong *)this + 8);
  while (cVar1 == '\0') {
    _Tree<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_>
    ::_Erase((_Tree<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_>
              *)this,(_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> *)
                     plVar3[2]);
    plVar2 = (longlong *)*plVar3;
    FUN_180002658(plVar3);
    plVar3 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x19);
  }
  *(longlong *)(*(longlong *)this + 8) = *(longlong *)this;
  *(undefined8 *)*(undefined8 *)this = *(undefined8 *)this;
  *(longlong *)(*(longlong *)this + 0x10) = *(longlong *)this;
  *(undefined8 *)(this + 8) = 0;
  FUN_180002658(*(undefined8 *)this);
  return;
}


/* ==================== _Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0> @ 18000470f  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class std::tuple<class meta::blocks::DeviceStreamBlock
   * __ptr64,struct std::_Ph<1> >,0>::_Compressed_pair<void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   std::tuple<class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> >,0>(class
   std::_Compressed_pair<void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData
   const * __ptr64) __ptr64,class std::tuple<class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> >,0> && __ptr64) __ptr64 */

_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
* __thiscall
std::
_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
::
_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
          (_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
           *this,_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(struct_royale::DepthData_const*___ptr64)___ptr64,class_std::tuple<class_meta::blocks::DeviceStreamBlock*___ptr64,struct_std::_Ph<1>_>,0>
                 *param_1)

{
                    /* 0x470f  1562
                       ??0?$_Compressed_pair@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZV?$tuple@PEAVDeviceStreamBlock@blocks@meta@@U?$_Ph@$00@std@@@std@@$0A@@std@@QEAA@$$QEAV01@@Z
                        */
  *(undefined8 *)this = *(undefined8 *)param_1;
  this[8] = *(_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
              *)(param_1 + 8);
  *(undefined8 *)(this + 0x10) = *(undefined8 *)(param_1 + 0x10);
  return this;
}


/* ==================== forward<coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180004840  (5 bytes) ==================== */

/* class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64
   __cdecl std::forward<class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64>(class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64) */

InputPort<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::forward<coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (InputPort<class_std::shared_ptr<struct_types::ImageFrame>_> **param_1)

{
                    /* 0x4840  1078
                       ??$forward@AEAPEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YAAEAPEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (InputPort<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== tuple<royale::DepthData_const*___ptr64&&___ptr64><royale::DepthData_const*___ptr64,0> @ 1800048f9  (5 bytes) ==================== */

/* public: __cdecl std::tuple<struct royale::DepthData const * __ptr64 && __ptr64>::tuple<struct
   royale::DepthData const * __ptr64 && __ptr64><struct royale::DepthData const * __ptr64,0>(struct
   royale::DepthData const * __ptr64 && __ptr64) __ptr64 */

tuple<royale::DepthData_const*___ptr64&&___ptr64> * __thiscall
std::tuple<royale::DepthData_const*___ptr64&&___ptr64>::
tuple<royale::DepthData_const*___ptr64&&___ptr64><royale::DepthData_const*___ptr64,0>
          (tuple<royale::DepthData_const*___ptr64&&___ptr64> *this,DepthData **param_1)

{
                    /* 0x48f9  199
                       ??$?0PEBUDepthData@royale@@$$V$0A@@?$tuple@$$QEAPEBUDepthData@royale@@@std@@QEAA@$$QEAPEBUDepthData@royale@@@Z
                        */
  *(DepthData ***)this = param_1;
  return this;
}


/* ==================== RgbFrameGrabber @ 180004971  (5 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* private: void __cdecl meta::blocks::DeviceStreamBlock::RgbFrameGrabber(class
   std::shared_ptr<struct sdc::ImageData> const & __ptr64) __ptr64 */

void __thiscall
meta::blocks::DeviceStreamBlock::RgbFrameGrabber
          (DeviceStreamBlock *this,shared_ptr<sdc::ImageData> *param_1)

{
  longlong *plVar1;
  int *piVar2;
  __uint64 *p_Var3;
  __uint64 *p_Var4;
  __uint64 _Var5;
  longlong lVar6;
  longlong lVar7;
  int iVar8;
  double dVar9;
  undefined1 auStackY_178 [32];
  __uint64 *p_Stack_148;
  longlong *plStack_140;
  undefined4 auStack_138 [2];
  undefined8 *puStack_130;
  undefined8 uStack_128;
  undefined4 auStack_120 [2];
  Mat *pMStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  longlong alStack_100 [3];
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  longlong lStack_b0;
  undefined8 *puStack_a8;
  undefined8 *puStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  Mat aMStack_88 [4];
  int iStack_84;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  longlong lStack_50;
  longlong lStack_48;
  undefined1 *puStack_40;
  undefined1 auStack_38 [16];
  ulonglong uStack_28;
  
                    /* 0x4971  3206
                       ?RgbFrameGrabber@DeviceStreamBlock@blocks@meta@@AEAAXAEBV?$shared_ptr@UImageData@sdc@@@std@@@Z
                        */
  uStack_108 = 0xfffffffffffffffe;
  uStack_28 = DAT_1802450f8 ^ (ulonglong)auStackY_178;
  lVar6 = *(longlong *)param_1;
  cv::Mat::Mat(aMStack_88,*(int *)(lVar6 + 8),*(int *)(lVar6 + 4),8,*(void **)(lVar6 + 0x10),0);
  uStack_e8 = _DAT_1800a1580;
  uStack_e0 = _UNK_1800a1588;
  uStack_d8 = 0;
  uStack_d0 = 0;
  uStack_c8 = 0;
  uStack_c0 = 0;
  uStack_b8 = 0;
  lStack_b0 = 0;
  puStack_a8 = &uStack_e0;
  puStack_a0 = &uStack_98;
  uStack_90 = 0;
  uStack_98 = 0;
  uStack_128 = 0;
  auStack_138[0] = 0x2010000;
  puStack_130 = &uStack_e8;
  uStack_110 = 0;
  auStack_120[0] = 0x1010000;
  pMStack_118 = aMStack_88;
  cv::cvtColor((_InputArray *)auStack_120,(_OutputArray *)auStack_138,0x6c,0);
  std::make_shared<types::ImageFrame>();
  cv::Mat::operator=((Mat *)(p_Stack_148 + 0xb),(Mat *)&uStack_e8);
  p_Var3 = p_Stack_148;
  _Var5 = device::Meta2FrameIdToUint64(*(undefined8 *)(*(longlong *)param_1 + 0x30));
  p_Var4 = p_Stack_148;
  *p_Var3 = _Var5;
  dVar9 = device::Meta2TimestampToSeconds(*(undefined8 *)(*(longlong *)param_1 + 0x28));
  p_Var4[1] = (__uint64)dVar9;
  lVar6 = _Query_perf_frequency();
  lVar7 = _Query_perf_counter();
  std::
  unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
  ::
  _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
            ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
              *)(p_Stack_148 + 2),
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)alStack_100);
  *(longlong *)(alStack_100[0] + 0x30) =
       ((lVar7 % lVar6) * 1000000000) / lVar6 + (lVar7 / lVar6) * 1000000000;
  (**(code **)(**(longlong **)(this + 0x388) + 8))(*(longlong **)(this + 0x388),&p_Stack_148);
  if (plStack_140 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_140 + 1;
    lVar6 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar6 == 1) {
      (**(code **)*plStack_140)(plStack_140);
      LOCK();
      piVar2 = (int *)((longlong)plStack_140 + 0xc);
      iVar8 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar8 == 1) {
        (**(code **)(*plStack_140 + 8))(plStack_140);
      }
    }
  }
  if (lStack_b0 != 0) {
    LOCK();
    piVar2 = (int *)(lStack_b0 + 0x14);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 == 1) {
      cv::Mat::deallocate((Mat *)&uStack_e8);
    }
  }
  lStack_b0 = 0;
  uStack_d8 = 0;
  uStack_c0 = 0;
  uStack_c8 = 0;
  uStack_d0 = 0;
  iVar8 = 0;
  if (0 < uStack_e8._4_4_) {
    lVar6 = 0;
    do {
      *(undefined4 *)(lVar6 + (longlong)puStack_a8) = 0;
      iVar8 = iVar8 + 1;
      lVar6 = lVar6 + 4;
    } while (iVar8 < uStack_e8._4_4_);
  }
  if (puStack_a0 != &uStack_98) {
    cv::fastFree(puStack_a0);
  }
  if (lStack_50 != 0) {
    LOCK();
    piVar2 = (int *)(lStack_50 + 0x14);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 == 1) {
      cv::Mat::deallocate(aMStack_88);
    }
  }
  lStack_50 = 0;
  uStack_78 = 0;
  uStack_60 = 0;
  uStack_68 = 0;
  uStack_70 = 0;
  iVar8 = 0;
  if (0 < iStack_84) {
    lVar6 = 0;
    do {
      *(undefined4 *)(lVar6 + lStack_48) = 0;
      iVar8 = iVar8 + 1;
      lVar6 = lVar6 + 4;
    } while (iVar8 < iStack_84);
  }
  if (puStack_40 != auStack_38) {
    cv::fastFree(puStack_40);
  }
  return;
}


/* ==================== _Compressed_pair<std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>,coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 1800049c1  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> > >,class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> > * __ptr64,1>::_Compressed_pair<struct std::default_delete<class
   coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > >,class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64,1><class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64>(struct
   std::_Zero_then_variadic_args_t,class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> > * __ptr64 & __ptr64) __ptr64 */

_Compressed_pair<std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>,coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
* __thiscall
std::
_Compressed_pair<std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>,coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
::
_Compressed_pair<std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>,coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>,coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x49c1  34
                       ??$?0AEAPEAV?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Compressed_pair@U?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@PEAV?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAV?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== _Uninitialized_move_al_unchecked<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>_>_> @ 180004a3e  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 __cdecl
   std::_Uninitialized_move_al_unchecked<class std::shared_ptr<struct types::ImageFrame> *
   __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64,class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> > >(class std::shared_ptr<struct types::ImageFrame> *
   __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64,class std::shared_ptr<struct
   types::ImageFrame> * __ptr64,class std::allocator<class std::shared_ptr<struct types::ImageFrame>
   > & __ptr64,struct std::_General_ptr_iterator_tag,struct std::_Unused_parameter) */

shared_ptr<types::ImageFrame> * __cdecl
std::
_Uninitialized_move_al_unchecked<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
          (undefined8 *param_1,undefined8 *param_2,shared_ptr<types::ImageFrame> *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 2) {
    *(undefined8 *)param_3 = *param_1;
    *(undefined8 *)(param_3 + 8) = param_1[1];
    *param_1 = 0;
    param_1[1] = 0;
    param_3 = param_3 + 0x10;
  }
  return param_3;
}


/* ==================== addressof<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_> @ 180004b10  (5 bytes) ==================== */

/* class std::_Tree_val<struct std::_Tree_simple_types<struct std::pair<unsigned int const ,struct
   sdc::TofConfig> > > * __ptr64 __cdecl std::addressof<class std::_Tree_val<struct
   std::_Tree_simple_types<struct std::pair<unsigned int const ,struct sdc::TofConfig> > > >(class
   std::_Tree_val<struct std::_Tree_simple_types<struct std::pair<unsigned int const ,struct
   sdc::TofConfig> > > & __ptr64) */

_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_> * __cdecl
std::
addressof<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_>
          (_Tree_val<struct_std::_Tree_simple_types<struct_std::pair<unsigned_int_const_,struct_sdc::TofConfig>_>_>
           *param_1)

{
                    /* 0x4b10  872
                       ??$addressof@V?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBIUTofConfig@sdc@@@std@@@std@@@std@@@std@@YAPEAV?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBIUTofConfig@sdc@@@std@@@std@@@0@AEAV10@@Z
                        */
  return (_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_> *)
         param_1;
}


/* ==================== _Unique_ptr_base<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_><coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64> @ 180004c00  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> > > >::_Unique_ptr_base<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> > > ><class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64>(class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64) __ptr64
    */

_Unique_ptr_base<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Unique_ptr_base<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Unique_ptr_base<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_><coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64>
          (_Unique_ptr_base<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,Buffer<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x4c00  147
                       ??$?0PEAV?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Unique_ptr_base@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(Buffer<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== make_unique<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,int&___ptr64,void> @ 180004d18  (5 bytes) ==================== */

/* class std::unique_ptr<class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > > >
   __cdecl std::make_unique<class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> >,int
   & __ptr64,void>(int & __ptr64) */

int * __cdecl
std::make_unique<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,int&___ptr64,void>(int *param_1)

{
  undefined8 *puVar1;
  int iVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  int *in_RDX;
  
                    /* 0x4d18  1315
                       ??$make_unique@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAHX@std@@YA?AV?$unique_ptr@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@0@AEAH@Z
                        */
  puVar3 = (undefined8 *)thunk_FUN_180084ee4(0x148);
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    iVar2 = *in_RDX;
    *puVar3 = coco::BufferBase<std::shared_ptr<types::ImageFrame>_>::vftable;
    *(undefined4 *)(puVar3 + 1) = 0;
    *(undefined1 *)((longlong)puVar3 + 0xc) = 0;
    coco::ConnectionStatisticsBuilder::ConnectionStatisticsBuilder
              ((ConnectionStatisticsBuilder *)(puVar3 + 2));
    *puVar3 = coco::Buffer<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar1 = puVar3 + 0x23;
    *puVar1 = 0;
    puVar3[0x24] = 0;
    puVar3[0x25] = 0;
    puVar3[0x26] = 0;
    puVar3[0x27] = 0;
    puVar4 = (undefined8 *)thunk_FUN_180084ee4(0x10);
    if (puVar4 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    *puVar1 = puVar4;
    *puVar4 = 0;
    puVar4[1] = 0;
    *(undefined8 **)*puVar1 = puVar1;
    puVar3[0x28] = (longlong)iVar2;
    puVar3[7] = (longlong)iVar2;
    puVar3[0x13] = 0x7ff0000000000000;
    puVar3[0x1b] = 0x7ff0000000000000;
    puVar3[0x1e] = 0;
    puVar3[8] = 0;
    puVar3[9] = 0;
    puVar3[0xe] = 0;
    puVar3[0xf] = 0;
    coco::ConnectionStatisticsBuilder::ResetProducerStats
              ((ConnectionStatisticsBuilder *)(puVar3 + 2));
    puVar3[0x10] = 0x7ff0000000000000;
  }
  *(undefined8 **)param_1 = puVar3;
  return param_1;
}


/* ==================== default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_><coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,void> @ 180004d9f  (5 bytes) ==================== */

/* public: __cdecl std::default_delete<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> > >::default_delete<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> > ><class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame>
   >,void>(struct std::default_delete<class coco::CircularBuffer<class std::shared_ptr<struct
   types::ImageFrame> > > const & __ptr64) __ptr64 */

default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>::
default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_><coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,void>
          (default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_> *this,
          default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_> *param_1)

{
                    /* 0x4d9f  229
                       ??$?0V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@X@?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@AEBU?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@1@@Z
                        */
  return this;
}


/* ==================== _Vector_alloc<std::_Vec_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_> @ 180004da9  (5 bytes) ==================== */

/* public: __cdecl std::_Vector_alloc<struct std::_Vec_base_types<class std::shared_ptr<struct
   types::ImageFrame>,class std::allocator<class std::shared_ptr<struct types::ImageFrame> > >
   >::_Vector_alloc<struct std::_Vec_base_types<class std::shared_ptr<struct
   types::ImageFrame>,class std::allocator<class std::shared_ptr<struct types::ImageFrame> > >
   >(void) __ptr64 */

_Vector_alloc<std::_Vec_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Vector_alloc<std::_Vec_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Vector_alloc<std::_Vec_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
          (_Vector_alloc<std::_Vec_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
                    /* 0x4da9  1728
                       ??0?$_Vector_alloc@U?$_Vec_base_types@V?$shared_ptr@UImageFrame@types@@@std@@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  return this;
}


/* ==================== unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_> @ 180004e21  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > >
   >::unique_ptr<class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> > > >(class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64) __ptr64 */

unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
::
unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x4e21  1907
                       ??0?$unique_ptr@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== _Unique_ptr_base<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_><coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64> @ 180004f11  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > >
   >::_Unique_ptr_base<class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> > > ><class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64>(class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > * __ptr64)
   __ptr64 */

_Unique_ptr_base<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Unique_ptr_base<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Unique_ptr_base<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_><coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64>
          (_Unique_ptr_base<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x4f11  164
                       ??$?0PEAV?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Unique_ptr_base@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== Mono1FrameGrabber @ 180004fb1  (5 bytes) ==================== */

/* private: void __cdecl meta::blocks::DeviceStreamBlock::Mono1FrameGrabber(class
   std::shared_ptr<struct sdc::ImageData> const & __ptr64) __ptr64 */

void __thiscall
meta::blocks::DeviceStreamBlock::Mono1FrameGrabber
          (DeviceStreamBlock *this,shared_ptr<sdc::ImageData> *param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  shared_ptr<sdc::ImageData> asStack_20 [8];
  longlong *plStack_18;
  
                    /* 0x4fb1  3118
                       ?Mono1FrameGrabber@DeviceStreamBlock@blocks@meta@@AEAAXAEBV?$shared_ptr@UImageData@sdc@@@std@@@Z
                        */
  CreateMonoImage(this,asStack_20);
  (**(code **)(**(longlong **)(this + 800) + 8))(*(longlong **)(this + 800),asStack_20);
  if (plStack_18 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_18 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_18)(plStack_18);
      LOCK();
      piVar2 = (int *)((longlong)plStack_18 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plStack_18 + 8))(plStack_18);
      }
    }
  }
  return;
}


/* ==================== _Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64> @ 180004ffc  (5 bytes) ==================== */

/* public: __cdecl std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64>::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64>(void (__cdecl meta::blocks::DeviceStreamBlock::*&& __ptr64)(struct royale::DepthData
   const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64 && __ptr64,struct
   std::_Ph<1> const & __ptr64) __ptr64 */

_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
* __thiscall
std::
_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
::
_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
           *this,void____cdecl_meta__blocks__DeviceStreamBlock________ptr64__royale__DepthData_const____ptr64____ptr64
                 *param_1,DeviceStreamBlock **param_2,_Ph<1> *param_3)

{
                    /* 0x4ffc  1546
                       ??0?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@QEAA@$$QEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@Z$$QEAPEAV234@AEBU?$_Ph@$00@1@@Z
                        */
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(DeviceStreamBlock **)(this + 0x10) = *param_2;
  return this;
}


/* ==================== shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> @ 180005056  (5 bytes) ==================== */

/* public: __cdecl std::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >(class std::shared_ptr<class coco::ConnectionTyped<class
   std::shared_ptr<struct types::ImageFrame> > > && __ptr64) __ptr64 */

shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
          (shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *this,
          shared_ptr<class_coco::ConnectionTyped<class_std::shared_ptr<struct_types::ImageFrame>_>_>
          *param_1)

{
                    /* 0x5056  1834
                       ??0?$shared_ptr@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@$$QEAV01@@Z
                        */
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  return this;
}


/* ==================== _Call_binder<std::_Unforced,0,1,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_> @ 18000509c  (5 bytes) ==================== */

/* void __cdecl std::_Call_binder<struct std::_Unforced,0,1,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   std::tuple<class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> >,class
   std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> >(struct std::_Invoker_ret<struct
   std::_Unforced,0>,struct std::integer_sequence<unsigned __int64,0,1>,void (__cdecl
   meta::blocks::DeviceStreamBlock::*& __ptr64)(struct royale::DepthData const * __ptr64)
   __ptr64,class std::tuple<class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> > &
   __ptr64,class std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> && __ptr64) */

void __cdecl
std::
_Call_binder<std::_Unforced,0,1,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_>
          (undefined8 param_1,undefined8 param_2,undefined8 *param_3,longlong param_4,
          undefined8 *param_5)

{
                    /* 0x509c  447
                       ??$_Call_binder@U_Unforced@std@@$0A@$00P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZV?$tuple@PEAVDeviceStreamBlock@blocks@meta@@U?$_Ph@$00@std@@@2@V?$tuple@$$QEAPEBUDepthData@royale@@@2@@std@@YAXU?$_Invoker_ret@U_Unforced@std@@$0A@@0@U?$integer_sequence@_K$0A@$00@0@AEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZAEAV?$tuple@PEAVDeviceStreamBlock@blocks@meta@@U?$_Ph@$00@std@@@0@$$QEAV?$tuple@$$QEAPEBUDepthData@royale@@@0@@Z
                        */
                    /* WARNING: Could not recover jumptable at 0x00018001a9af. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)*param_3)(*(undefined8 *)(param_4 + 8),*(undefined8 *)*param_5);
  return;
}


/* ==================== ~_Tree<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_> @ 1800050dd  (5 bytes) ==================== */

/* public: __cdecl std::_Tree<class std::_Tmap_traits<unsigned int,struct sdc::TofConfig,struct
   std::less<unsigned int>,class std::allocator<struct std::pair<unsigned int const ,struct
   sdc::TofConfig> >,0> >::~_Tree<class std::_Tmap_traits<unsigned int,struct sdc::TofConfig,struct
   std::less<unsigned int>,class std::allocator<struct std::pair<unsigned int const ,struct
   sdc::TofConfig> >,0> >(void) __ptr64 */

void __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_>
::
~_Tree<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_>
          (_Tree<std::_Tmap_traits<unsigned_int,sdc::TofConfig,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const_,sdc::TofConfig>_>,0>_>
           *this)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
                    /* 0x50dd  2199
                       ??1?$_Tree@V?$_Tmap_traits@IUTofConfig@sdc@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUTofConfig@sdc@@@std@@@4@$0A@@std@@@std@@QEAA@XZ
                        */
  cVar1 = *(char *)((longlong)*(longlong **)(*(longlong *)this + 8) + 0x19);
  plVar3 = *(longlong **)(*(longlong *)this + 8);
  while (cVar1 == '\0') {
    _Erase(this,(_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> *)plVar3[2]
          );
    plVar2 = (longlong *)*plVar3;
    FUN_180002658(plVar3);
    plVar3 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x19);
  }
  *(longlong *)(*(longlong *)this + 8) = *(longlong *)this;
  *(undefined8 *)*(undefined8 *)this = *(undefined8 *)this;
  *(longlong *)(*(longlong *)this + 0x10) = *(longlong *)this;
  *(undefined8 *)(this + 8) = 0;
  FUN_180002658(*(undefined8 *)this);
  return;
}


/* ==================== _Unique_ptr_base<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_><royale::IDepthDataListener*___ptr64> @ 180005119  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class royale::IDepthDataListener,struct
   std::default_delete<class royale::IDepthDataListener> >::_Unique_ptr_base<class
   royale::IDepthDataListener,struct std::default_delete<class royale::IDepthDataListener> ><class
   royale::IDepthDataListener * __ptr64>(class royale::IDepthDataListener * __ptr64) __ptr64 */

_Unique_ptr_base<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_> *
__thiscall
std::_Unique_ptr_base<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>::
_Unique_ptr_base<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_><royale::IDepthDataListener*___ptr64>
          (_Unique_ptr_base<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>
           *this,IDepthDataListener *param_1)

{
                    /* 0x5119  192
                       ??$?0PEAVIDepthDataListener@royale@@@?$_Unique_ptr_base@VIDepthDataListener@royale@@U?$default_delete@VIDepthDataListener@royale@@@std@@@std@@QEAA@PEAVIDepthDataListener@royale@@@Z
                        */
  *(IDepthDataListener **)this = param_1;
  return this;
}


/* ==================== function<void___cdecl(royale::DepthData_const*___ptr64)><std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void> @ 180005227  (5 bytes) ==================== */

/* public: __cdecl std::function<void __cdecl(struct royale::DepthData const *
   __ptr64)>::function<void __cdecl(struct royale::DepthData const * __ptr64)><class
   std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64>,void>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64>) __ptr64 */

function<void___cdecl(royale::DepthData_const*___ptr64)> * __thiscall
std::function<void___cdecl(royale::DepthData_const*___ptr64)>::
function<void___cdecl(royale::DepthData_const*___ptr64)><std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void>
          (function<void___cdecl(royale::DepthData_const*___ptr64)> *this,undefined8 *param_2)

{
                    /* 0x5227  284
                       ??$?0V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@X@?$function@$$A6AXPEBUDepthData@royale@@@Z@std@@QEAA@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@1@@Z
                        */
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined ***)this =
       _Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
       ::vftable;
  *(undefined8 *)(this + 8) = *param_2;
  this[0x10] = *(function<void___cdecl(royale::DepthData_const*___ptr64)> *)(param_2 + 1);
  *(undefined8 *)(this + 0x18) = param_2[2];
  *(function<void___cdecl(royale::DepthData_const*___ptr64)> **)(this + 0x38) = this;
  return this;
}


/* ==================== _Compressed_pair<std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>,coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180005335  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class coco::Buffer<class
   std::shared_ptr<struct types::ImageFrame> > >,class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> > * __ptr64,1>::_Compressed_pair<struct std::default_delete<class
   coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > >,class coco::Buffer<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64,1><class coco::Buffer<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64>(struct
   std::_Zero_then_variadic_args_t,class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> > * __ptr64 & __ptr64) __ptr64 */

_Compressed_pair<std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>,coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
* __thiscall
std::
_Compressed_pair<std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>,coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
::
_Compressed_pair<std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>,coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>,coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x5335  28
                       ??$?0AEAPEAV?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Compressed_pair@U?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@PEAV?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAV?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== forward<void_(__cdecl_meta::blocks::DeviceStreamBlock::*&___ptr64)(royale::DepthData_const*___ptr64)___ptr64> @ 18000534e  (5 bytes) ==================== */

/* void (__cdecl meta::blocks::DeviceStreamBlock::*& __ptr64 __cdecl std::forward<void (__cdecl
   meta::blocks::DeviceStreamBlock::*& __ptr64)(struct royale::DepthData const * __ptr64)
   __ptr64>(void (__cdecl meta::blocks::DeviceStreamBlock::*& __ptr64)(struct royale::DepthData
   const * __ptr64) __ptr64))(struct royale::DepthData const * __ptr64) __ptr64 */

_func_void_DepthData_ptr ** __cdecl
std::
forward<void_(__cdecl_meta::blocks::DeviceStreamBlock::*&___ptr64)(royale::DepthData_const*___ptr64)___ptr64>
          (_func_void_DepthData_ptr **param_1)

{
                    /* 0x534e  1025
                       ??$forward@AEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@Z@std@@YAAEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZAEAP8123@EAAX0@Z@Z
                        */
  return param_1;
}


/* ==================== _Uninitialized_copy<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_> @ 180005362  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 __cdecl
   std::_Uninitialized_copy<class std::shared_ptr<struct types::ImageFrame> * __ptr64 *
   __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> * __ptr64> >(class
   std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,class std::shared_ptr<struct
   types::ImageFrame> * __ptr64 * __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64
   * __ptr64,class std::allocator<class std::shared_ptr<struct types::ImageFrame> * __ptr64> &
   __ptr64) */

shared_ptr<types::ImageFrame> ** __cdecl
std::
_Uninitialized_copy<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_>
          (shared_ptr<struct_types::ImageFrame> **param_1,
          shared_ptr<struct_types::ImageFrame> **param_2,
          shared_ptr<struct_types::ImageFrame> **param_3,
          allocator<std::shared_ptr<types::ImageFrame>*___ptr64> *param_4)

{
                    /* 0x5362  723
                       ??$_Uninitialized_copy@PEAPEAV?$shared_ptr@UImageFrame@types@@@std@@PEAPEAV12@V?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@YAPEAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAPEAV10@00AEAV?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@0@@Z
                        */
  memmove(param_3,param_1,(longlong)param_2 - (longlong)param_1);
  return (shared_ptr<types::ImageFrame> **)
         (((longlong)param_2 - (longlong)param_1) + (longlong)param_3);
}


/* ==================== forward<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 1800053df  (5 bytes) ==================== */

/* class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64
   __cdecl std::forward<class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >
   * __ptr64 & __ptr64>(class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >
   * __ptr64 & __ptr64) */

CircularBuffer<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::forward<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (CircularBuffer<class_std::shared_ptr<struct_types::ImageFrame>_> **param_1)

{
                    /* 0x53df  1049
                       ??$forward@AEAPEAV?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YAAEAPEAV?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (CircularBuffer<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== _Test_callable<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_> @ 18000543e  (5 bytes) ==================== */

/* bool __cdecl std::_Test_callable<class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> >(class
   std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64> const & __ptr64,struct std::integral_constant<bool,0>) */

bool __cdecl
std::
_Test_callable<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_>
          (void)

{
                    /* 0x543e  666
                       ??$_Test_callable@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@@std@@YA_NAEBV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@U?$integral_constant@_N$0A@@0@@Z
                        */
  return true;
}


/* ==================== ~ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> @ 18000548e  (5 bytes) ==================== */

/* public: virtual __cdecl coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> >::~ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>::
~ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x548e  2063
                       ??1?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ
                        */
  std::
  vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
  ::_Tidy((vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
           *)(this + 0x10));
  return;
}


/* ==================== ~Buffer<std::shared_ptr<types::ImageFrame>_> @ 1800054de  (5 bytes) ==================== */

/* public: virtual __cdecl coco::Buffer<class std::shared_ptr<struct types::ImageFrame>
   >::~Buffer<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::Buffer<std::shared_ptr<types::ImageFrame>_>::~Buffer<std::shared_ptr<types::ImageFrame>_>
          (Buffer<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x54de  2023
                       ??1?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ */
  std::
  deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>::
  _Tidy((deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
         *)(this + 0x118));
  FUN_180002658(*(undefined8 *)(this + 0x118));
  *(undefined8 *)(this + 0x118) = 0;
  std::vector<unsigned___int64,std::allocator<unsigned___int64>_>::_Tidy
            ((vector<unsigned___int64,std::allocator<unsigned___int64>_> *)(this + 0x100));
  std::
  deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
  ::
  ~deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
            ((deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
              *)(this + 0x10));
  return;
}


/* ==================== unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_> @ 180005501  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class royale::IDepthDataListener,struct std::default_delete<class
   royale::IDepthDataListener> >::unique_ptr<class royale::IDepthDataListener,struct
   std::default_delete<class royale::IDepthDataListener> >(void) __ptr64 */

unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_> * __thiscall
std::unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>::
unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>
          (unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>
           *this)

{
                    /* 0x5501  1916
                       ??0?$unique_ptr@VIDepthDataListener@royale@@U?$default_delete@VIDepthDataListener@royale@@@std@@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  return this;
}


/* ==================== move<types::ImageFrame*___ptr64&___ptr64> @ 18000552e  (5 bytes) ==================== */

/* struct types::ImageFrame * __ptr64 && __ptr64 __cdecl std::move<struct types::ImageFrame *
   __ptr64 & __ptr64>(struct types::ImageFrame * __ptr64 & __ptr64) */

ImageFrame ** __cdecl std::move<types::ImageFrame*___ptr64&___ptr64>(ImageFrame **param_1)

{
                    /* 0x552e  1356
                       ??$move@AEAPEAUImageFrame@types@@@std@@YA$$QEAPEAUImageFrame@types@@AEAPEAU12@@Z
                        */
  return param_1;
}


/* ==================== CreateTofImageFramePtr @ 180005579  (5 bytes) ==================== */

/* protected: class std::shared_ptr<struct types::ImageFrame> __cdecl
   meta::blocks::DeviceStreamBlock::CreateTofImageFramePtr(class cv::Mat const &
   __ptr64,double,class std::chrono::time_point<struct std::chrono::steady_clock,class
   std::chrono::duration<__int64,struct std::ratio<1,1000000000> > > const & __ptr64)const __ptr64
    */

Mat * __thiscall
meta::blocks::DeviceStreamBlock::CreateTofImageFramePtr
          (DeviceStreamBlock *this,Mat *param_1,double param_2,
          time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>
          *param_3)

{
  Mat *in_R8;
  undefined4 in_XMM3_Da;
  undefined4 in_XMM3_Db;
  undefined8 *in_stack_00000028;
  longlong alStack_28 [4];
  
                    /* 0x5579  3023
                       ?CreateTofImageFramePtr@DeviceStreamBlock@blocks@meta@@IEBA?AV?$shared_ptr@UImageFrame@types@@@std@@AEBVMat@cv@@NAEBV?$time_point@Usteady_clock@chrono@std@@V?$duration@_JU?$ratio@$00$0DLJKMKAA@@std@@@23@@chrono@5@@Z
                        */
  std::make_shared<types::ImageFrame>();
  cv::Mat::operator=((Mat *)(*(longlong *)param_1 + 0x58),in_R8);
  **(undefined8 **)param_1 = *(undefined8 *)(this + 0x8e8);
  *(ulonglong *)(*(longlong *)param_1 + 8) = CONCAT44(in_XMM3_Db,in_XMM3_Da);
  std::
  unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
  ::
  _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
            ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
              *)(*(longlong *)param_1 + 0x10),
             (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)alStack_28);
  *(undefined8 *)(alStack_28[0] + 0x30) = *in_stack_00000028;
  return param_1;
}


/* ==================== ~unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_> @ 1800055b5  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > >
   >::~unique_ptr<class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> > > >(void) __ptr64 */

void __thiscall
std::
unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
::
~unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x55b5  2360
                       ??1?$unique_ptr@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0001800310a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== forward<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_> @ 18000560a  (5 bytes) ==================== */

/* class std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64> && __ptr64 __cdecl std::forward<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> >(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> & __ptr64) */

_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
* __cdecl std::
          forward<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_>
                    (_Binder<struct_std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(struct_royale::DepthData_const*___ptr64)___ptr64,class_meta::blocks::DeviceStreamBlock*___ptr64,struct_std::_Ph<1>_const&___ptr64>
                     *param_1)

{
                    /* 0x560a  1231
                       ??$forward@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@@std@@YA$$QEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@AEAV10@@Z
                        */
  return (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          *)param_1;
}


/* ==================== _Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64> @ 180005704  (5 bytes) ==================== */

/* public: __cdecl std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64>::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> const & __ptr64)
   __ptr64 */

_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
* __thiscall
std::
_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
::
_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
           *this,_Binder<struct_std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(struct_royale::DepthData_const*___ptr64)___ptr64,class_meta::blocks::DeviceStreamBlock*___ptr64,struct_std::_Ph<1>_const&___ptr64>
                 *param_1)

{
                    /* 0x5704  1548
                       ??0?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@QEAA@AEBV01@@Z
                        */
  *(undefined8 *)this = *(undefined8 *)param_1;
  this[8] = *(_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
              *)(param_1 + 8);
  *(undefined8 *)(this + 0x10) = *(undefined8 *)(param_1 + 0x10);
  return this;
}


/* ==================== _Reset<types::ImageFrame> @ 1800057b8  (5 bytes) ==================== */

/* public: void __cdecl std::_Ptr_base<struct types::ImageFrame>::_Reset<struct
   types::ImageFrame>(class std::_Ptr_base<struct types::ImageFrame> const & __ptr64) __ptr64 */

void __thiscall
std::_Ptr_base<types::ImageFrame>::_Reset<types::ImageFrame>
          (_Ptr_base<types::ImageFrame> *this,_Ptr_base<struct_types::ImageFrame> *param_1)

{
  _Ref_count_base *p_Var1;
  ImageFrame *pIVar2;
  
                    /* 0x57b8  610
                       ??$_Reset@UImageFrame@types@@@?$_Ptr_base@UImageFrame@types@@@std@@QEAAXAEBV01@@Z
                        */
  p_Var1 = *(_Ref_count_base **)(param_1 + 8);
  pIVar2 = *(ImageFrame **)param_1;
  if (p_Var1 != (_Ref_count_base *)0x0) {
    LOCK();
    *(int *)(p_Var1 + 8) = *(int *)(p_Var1 + 8) + 1;
    UNLOCK();
  }
  _Reset0(this,pIVar2,p_Var1);
  return;
}


/* ==================== ~_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> @ 18000582b  (5 bytes) ==================== */

/* public: virtual __cdecl std::_Ref_count_obj<class coco::ConnectionTyped<class
   std::shared_ptr<struct types::ImageFrame> > >::~_Ref_count_obj<class coco::ConnectionTyped<class
   std::shared_ptr<struct types::ImageFrame> > >(void) __ptr64 */

void __thiscall
std::_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
~_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
          (_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *this)

{
                    /* 0x582b  2184
                       ??1?$_Ref_count_obj@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@UEAA@XZ
                        */
  *(undefined ***)this = _Ref_count_base::vftable;
  return;
}


/* ==================== forward<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64> @ 180005853  (5 bytes) ==================== */

/* class std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64> & __ptr64 __cdecl std::forward<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> & __ptr64>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> & __ptr64) */

_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
* __cdecl std::
          forward<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64>
                    (_Binder<struct_std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(struct_royale::DepthData_const*___ptr64)___ptr64,class_meta::blocks::DeviceStreamBlock*___ptr64,struct_std::_Ph<1>_const&___ptr64>
                     *param_1)

{
                    /* 0x5853  1108
                       ??$forward@AEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@@std@@YAAEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@AEAV10@@Z
                        */
  return (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          *)param_1;
}


/* ==================== Data_RegisterNewBogus1Frame @ 1800058b7  (5 bytes) ==================== */

/* public: virtual enum sdc::EventHandlerStatus __cdecl
   sdc::EventHandlerAdapter::Data_RegisterNewBogus1Frame(class std::function<void __cdecl(class
   std::shared_ptr<struct sdc::ImageData> const & __ptr64)>) __ptr64 */

EventHandlerStatus __thiscall
sdc::EventHandlerAdapter::Data_RegisterNewBogus1Frame(undefined8 param_1,longlong *param_2)

{
  longlong *plVar1;
  
                    /* 0x58b7  3032
                       ?Data_RegisterNewBogus1Frame@EventHandlerAdapter@sdc@@UEAA?AW4EventHandlerStatus@2@V?$function@$$A6AXAEBV?$shared_ptr@UImageData@sdc@@@std@@@Z@std@@@Z
                        */
  plVar1 = (longlong *)param_2[7];
  if (plVar1 != (longlong *)0x0) {
    (**(code **)(*plVar1 + 0x20))(plVar1,plVar1 != param_2);
    param_2[7] = 0;
  }
  return 0;
}


/* ==================== destroy<std::shared_ptr<types::ImageFrame>_> @ 180005957  (5 bytes) ==================== */

/* public: static void __cdecl std::_Default_allocator_traits<class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> > >::destroy<class std::shared_ptr<struct
   types::ImageFrame> >(class std::allocator<class std::shared_ptr<struct types::ImageFrame> > &
   __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64 const) */

void __cdecl
std::_Default_allocator_traits<std::allocator<std::shared_ptr<types::ImageFrame>_>_>::
destroy<std::shared_ptr<types::ImageFrame>_>
          (allocator<std::shared_ptr<types::ImageFrame>_> *param_1,
          shared_ptr<types::ImageFrame> *param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  
                    /* 0x5957  998
                       ??$destroy@V?$shared_ptr@UImageFrame@types@@@std@@@?$_Default_allocator_traits@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@SAXAEAV?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@1@QEAV?$shared_ptr@UImageFrame@types@@@1@@Z
                        */
  plVar4 = *(longlong **)(param_2 + 8);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}


/* ==================== shared_ptr<types::ImageFrame> @ 180005975  (5 bytes) ==================== */

/* public: __cdecl std::shared_ptr<struct types::ImageFrame>::shared_ptr<struct
   types::ImageFrame>(class std::shared_ptr<struct types::ImageFrame> && __ptr64) __ptr64 */

shared_ptr<types::ImageFrame> * __thiscall
std::shared_ptr<types::ImageFrame>::shared_ptr<types::ImageFrame>
          (shared_ptr<types::ImageFrame> *this,shared_ptr<struct_types::ImageFrame> *param_1)

{
                    /* 0x5975  1823  ??0?$shared_ptr@UImageFrame@types@@@std@@QEAA@$$QEAV01@@Z */
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  return this;
}


/* ==================== PassThroughPort<std::shared_ptr<types::ImageFrame>_> @ 1800059d4  (5 bytes) ==================== */

/* void __cdecl meta::blocks::PassThroughPort<class std::shared_ptr<struct types::ImageFrame>
   >(class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > & __ptr64,class
   coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > & __ptr64) */

void __cdecl
meta::blocks::PassThroughPort<std::shared_ptr<types::ImageFrame>_>
          (InputPort<std::shared_ptr<types::ImageFrame>_> *param_1,
          OutputPort<std::shared_ptr<types::ImageFrame>_> *param_2)

{
  longlong *plVar1;
  int *piVar2;
  undefined8 *puVar3;
  longlong lVar4;
  longlong *plVar5;
  int iVar6;
  undefined8 *puVar7;
  undefined8 in_R8;
  undefined8 in_R9;
  undefined8 uVar8;
  undefined8 uStack_20;
  longlong *plStack_18;
  
                    /* 0x59d4  395
                       ??$PassThroughPort@V?$shared_ptr@UImageFrame@types@@@std@@@blocks@meta@@YAXAEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@3@@Z
                        */
  uVar8 = 0xfffffffffffffffe;
  puVar7 = *(undefined8 **)(*(longlong *)(param_1 + 8) + 0x10);
  puVar3 = *(undefined8 **)(*(longlong *)(param_1 + 8) + 0x18);
  while( true ) {
    if (puVar7 == puVar3) {
      return;
    }
    iVar6 = (**(code **)(*(longlong *)*puVar7 + 8))();
    if (iVar6 == 2) break;
    puVar7 = puVar7 + 2;
  }
  uStack_20 = 0;
  plStack_18 = (longlong *)0x0;
  (**(code **)(**(longlong **)(param_1 + 0x60) + 8))
            (*(longlong **)(param_1 + 0x60),&uStack_20,in_R8,in_R9,uVar8);
  (**(code **)(**(longlong **)(param_2 + 0x60) + 8))(*(longlong **)(param_2 + 0x60),&uStack_20);
  plVar5 = plStack_18;
  if (plStack_18 == (longlong *)0x0) {
    return;
  }
  LOCK();
  plVar1 = plStack_18 + 1;
  lVar4 = *plVar1;
  *(int *)plVar1 = (int)*plVar1 + -1;
  UNLOCK();
  if ((int)lVar4 != 1) {
    return;
  }
  (**(code **)*plStack_18)(plStack_18);
  LOCK();
  piVar2 = (int *)((longlong)plVar5 + 0xc);
  iVar6 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (iVar6 == 1) {
    (**(code **)(*plVar5 + 8))(plVar5);
    return;
  }
  return;
}


/* ==================== move<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64> @ 180005a92  (5 bytes) ==================== */

/* class std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64> && __ptr64 __cdecl std::move<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> & __ptr64>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> & __ptr64) */

_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
* __cdecl std::
          move<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64>
                    (_Binder<struct_std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(struct_royale::DepthData_const*___ptr64)___ptr64,class_meta::blocks::DeviceStreamBlock*___ptr64,struct_std::_Ph<1>_const&___ptr64>
                     *param_1)

{
                    /* 0x5a92  1369
                       ??$move@AEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@@std@@YA$$QEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@AEAV10@@Z
                        */
  return (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          *)param_1;
}


/* ==================== swap<types::ImageFrame*___ptr64,void> @ 180005ace  (5 bytes) ==================== */

/* void __cdecl std::swap<struct types::ImageFrame * __ptr64,void>(struct types::ImageFrame *
   __ptr64 & __ptr64,struct types::ImageFrame * __ptr64 & __ptr64) */

void __cdecl std::swap<types::ImageFrame*___ptr64,void>(ImageFrame **param_1,ImageFrame **param_2)

{
  ImageFrame *pIVar1;
  
                    /* 0x5ace  1412
                       ??$swap@PEAUImageFrame@types@@X@std@@YAXAEAPEAUImageFrame@types@@0@Z */
  pIVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pIVar1;
  return;
}


/* ==================== _Uninitialized_copy_al_unchecked<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_> @ 180005af6  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 __cdecl
   std::_Uninitialized_copy_al_unchecked<class std::shared_ptr<struct types::ImageFrame> *
   __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64,class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> * __ptr64> >(class std::shared_ptr<struct
   types::ImageFrame> * __ptr64 * __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64
   * __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> * __ptr64> & __ptr64,struct
   std::_Really_trivial_ptr_iterator_tag,struct std::integral_constant<bool,1>) */

shared_ptr<types::ImageFrame> ** __cdecl
std::
_Uninitialized_copy_al_unchecked<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_>
          (void *param_1,longlong param_2,void *param_3)

{
                    /* 0x5af6  732
                       ??$_Uninitialized_copy_al_unchecked@PEAV?$shared_ptr@UImageFrame@types@@@std@@PEAV12@V?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@YAPEAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAPEAV10@00AEAV?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@0@U_Really_trivial_ptr_iterator_tag@0@U?$integral_constant@_N$00@0@@Z
                        */
  memmove(param_3,param_1,param_2 - (longlong)param_1);
  return (shared_ptr<types::ImageFrame> **)((param_2 - (longlong)param_1) + (longlong)param_3);
}


/* ==================== _Compressed_pair<std::default_delete<RoyaleDataListener>,RoyaleDataListener*___ptr64,1><RoyaleDataListener*___ptr64&___ptr64> @ 180005b91  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class RoyaleDataListener>,class
   RoyaleDataListener * __ptr64,1>::_Compressed_pair<struct std::default_delete<class
   RoyaleDataListener>,class RoyaleDataListener * __ptr64,1><class RoyaleDataListener * __ptr64 &
   __ptr64>(struct std::_Zero_then_variadic_args_t,class RoyaleDataListener * __ptr64 & __ptr64)
   __ptr64 */

_Compressed_pair<std::default_delete<RoyaleDataListener>,RoyaleDataListener*___ptr64,1> * __thiscall
std::_Compressed_pair<std::default_delete<RoyaleDataListener>,RoyaleDataListener*___ptr64,1>::
_Compressed_pair<std::default_delete<RoyaleDataListener>,RoyaleDataListener*___ptr64,1><RoyaleDataListener*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<RoyaleDataListener>,RoyaleDataListener*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x5b91  78
                       ??$?0AEAPEAVRoyaleDataListener@@@?$_Compressed_pair@U?$default_delete@VRoyaleDataListener@@@std@@PEAVRoyaleDataListener@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAVRoyaleDataListener@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== ~unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_> @ 180005bb9  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::Data<class std::shared_ptr<struct types::ImageFrame>
   >,struct std::default_delete<class coco::Data<class std::shared_ptr<struct types::ImageFrame> > >
   >::~unique_ptr<class coco::Data<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::Data<class std::shared_ptr<struct types::ImageFrame> > > >(void)
   __ptr64 */

void __thiscall
std::
unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
::
~unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x5bb9  2372
                       ??1?$unique_ptr@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0001800311e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== make_shared<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>,coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64,coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64,coco::ConnectionPolicy&___ptr64> @ 180005be1  (5 bytes) ==================== */

/* class std::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct types::ImageFrame>
   > > __cdecl std::make_shared<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> >,class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64,struct coco::ConnectionPolicy & __ptr64>(class coco::InputPort<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 && __ptr64,class coco::OutputPort<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64,struct coco::ConnectionPolicy &
   __ptr64) */

InputPort<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::
make_shared<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>,coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64,coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64,coco::ConnectionPolicy&___ptr64>
          (InputPort<std::shared_ptr<types::ImageFrame>_> **param_1,
          OutputPort<std::shared_ptr<types::ImageFrame>_> **param_2,ConnectionPolicy *param_3)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  _Ref_count_base *p_Var6;
  undefined4 *in_R9;
  
                    /* 0x5be1  1306
                       ??$make_shared@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@PEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@2@AEAPEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@2@AEAUConnectionPolicy@2@@std@@YA?AV?$shared_ptr@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@0@$$QEAPEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@3@AEAUConnectionPolicy@3@@Z
                        */
  p_Var6 = (_Ref_count_base *)thunk_FUN_180084ee4(0xf0);
  if (p_Var6 == (_Ref_count_base *)0x0) {
    p_Var6 = (_Ref_count_base *)0x0;
  }
  else {
    *(undefined4 *)(p_Var6 + 8) = 1;
    *(undefined4 *)(p_Var6 + 0xc) = 1;
    *(undefined ***)p_Var6 =
         _Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::vftable;
    uVar1 = *(undefined8 *)param_3;
    uVar2 = *in_R9;
    uVar3 = in_R9[1];
    uVar4 = in_R9[2];
    uVar5 = in_R9[3];
    *(OutputPort<std::shared_ptr<types::ImageFrame>_> **)(p_Var6 + 0x18) = *param_2;
    *(undefined8 *)(p_Var6 + 0x20) = uVar1;
    *(undefined4 *)(p_Var6 + 0x28) = uVar2;
    *(undefined4 *)(p_Var6 + 0x2c) = uVar3;
    *(undefined4 *)(p_Var6 + 0x30) = uVar4;
    *(undefined4 *)(p_Var6 + 0x34) = uVar5;
    *(undefined8 *)(p_Var6 + 0x38) = 0;
    p_Var6[0x40] = (_Ref_count_base)0x0;
    *(undefined ***)(p_Var6 + 0x10) =
         coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::vftable;
    *(undefined8 *)(p_Var6 + 0x48) = 0;
    *(undefined8 *)(p_Var6 + 0x50) = 0;
    _Mtx_init_in_situ(p_Var6 + 0x58,2);
    _Cnd_init_in_situ(p_Var6 + 0xa8);
    coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::CreateConnection
              ((ConnectionTyped<std::shared_ptr<types::ImageFrame>_> *)(p_Var6 + 0x10));
  }
  *param_1 = (InputPort<std::shared_ptr<types::ImageFrame>_> *)0x0;
  param_1[1] = (InputPort<std::shared_ptr<types::ImageFrame>_> *)0x0;
  shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
  _Resetp0<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
            ((shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *)param_1,
             (ConnectionTyped<std::shared_ptr<types::ImageFrame>_> *)(p_Var6 + 0x10),p_Var6);
  return param_1;
}


/* ==================== ~deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_> @ 180005ce5  (5 bytes) ==================== */

/* public: __cdecl std::deque<class std::shared_ptr<struct types::ImageFrame>,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> > >::~deque<class
   std::shared_ptr<struct types::ImageFrame>,class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

void __thiscall
std::deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
::~deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
          (deque<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
           *this)

{
                    /* 0x5ce5  2236
                       ??1?$deque@V?$shared_ptr@UImageFrame@types@@@std@@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@QEAA@XZ
                        */
  _Tidy(this);
  FUN_180002658(*(undefined8 *)this);
  *(undefined8 *)this = 0;
  return;
}


/* ==================== ~OutputPort<std::shared_ptr<types::ImageFrame>_> @ 180005cef  (5 bytes) ==================== */

/* public: virtual __cdecl coco::OutputPort<class std::shared_ptr<struct types::ImageFrame>
   >::~OutputPort<class std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::OutputPort<std::shared_ptr<types::ImageFrame>_>::
~OutputPort<std::shared_ptr<types::ImageFrame>_>
          (OutputPort<std::shared_ptr<types::ImageFrame>_> *this)

{
  undefined8 *puVar1;
  
                    /* 0x5cef  2097
                       ??1?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ */
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(this + 0x38));
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::_Tidy_deallocate
            ((basic_string<char,std::char_traits<char>,std::allocator<char>_> *)(this + 0x18));
  puVar1 = *(undefined8 **)(this + 8);
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00018002d251. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== _Resetp0<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> @ 180005d2b  (5 bytes) ==================== */

/* public: void __cdecl std::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >::_Resetp0<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >(class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > * __ptr64,class std::_Ref_count_base * __ptr64) __ptr64 */

void __thiscall
std::shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
_Resetp0<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
          (shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *this,
          ConnectionTyped<std::shared_ptr<types::ImageFrame>_> *param_1,_Ref_count_base *param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  
                    /* 0x5d2b  642
                       ??$_Resetp0@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$shared_ptr@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAAXPEAV?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@PEAV_Ref_count_base@1@@Z
                        */
  plVar4 = *(longlong **)(this + 8);
  if (plVar4 == (longlong *)0x0) {
    *(_Ref_count_base **)(this + 8) = param_2;
    *(ConnectionTyped<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  }
  else {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
      *(_Ref_count_base **)(this + 8) = param_2;
      *(ConnectionTyped<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
    }
    else {
      *(_Ref_count_base **)(this + 8) = param_2;
      *(ConnectionTyped<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
    }
  }
  return;
}


/* ==================== ~shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> @ 180005d3a  (5 bytes) ==================== */

/* public: __cdecl std::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >::~shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

void __thiscall
std::shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
~shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
          (shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *this)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  
                    /* 0x5d3a  2310
                       ??1?$shared_ptr@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@XZ
                        */
  plVar4 = *(longlong **)(this + 8);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}


/* ==================== ~unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_> @ 180005d71  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class RoyaleDataListener,struct std::default_delete<class
   RoyaleDataListener> >::~unique_ptr<class RoyaleDataListener,struct std::default_delete<class
   RoyaleDataListener> >(void) __ptr64 */

void __thiscall
std::unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_>::
~unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_>
          (unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_> *this)

{
  undefined8 *puVar1;
  
                    /* 0x5d71  2380
                       ??1?$unique_ptr@VRoyaleDataListener@@U?$default_delete@VRoyaleDataListener@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0001800312e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== allocator<std::shared_ptr<types::ImageFrame>_> @ 180005d76  (5 bytes) ==================== */

/* public: __cdecl std::allocator<class std::shared_ptr<struct types::ImageFrame> >::allocator<class
   std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

allocator<std::shared_ptr<types::ImageFrame>_> * __thiscall
std::allocator<std::shared_ptr<types::ImageFrame>_>::allocator<std::shared_ptr<types::ImageFrame>_>
          (allocator<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x5d76  1746
                       ??0?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@std@@QEAA@XZ */
  return this;
}


/* ==================== _Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_> @ 180005d7b  (5 bytes) ==================== */

/* public: __cdecl std::_Tree_const_iterator<class std::_Tree_val<struct
   std::_Tree_simple_types<struct std::pair<unsigned int const ,struct sdc::TofConfig> > >
   >::_Tree_const_iterator<class std::_Tree_val<struct std::_Tree_simple_types<struct
   std::pair<unsigned int const ,struct sdc::TofConfig> > > >(struct std::_Tree_node<struct
   std::pair<unsigned int const ,struct sdc::TofConfig>,void * __ptr64> * __ptr64,class
   std::_Tree_val<struct std::_Tree_simple_types<struct std::pair<unsigned int const ,struct
   sdc::TofConfig> > > const * __ptr64) __ptr64 */

_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_>
* __thiscall
std::
_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_>
::
_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_>
          (_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>_>
           *this,_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> *param_1,
          _Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>
          *param_2)

{
                    /* 0x5d7b  1684
                       ??0?$_Tree_const_iterator@V?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBIUTofConfig@sdc@@@std@@@std@@@std@@@std@@QEAA@PEAU?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@1@PEBV?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBIUTofConfig@sdc@@@std@@@std@@@1@@Z
                        */
  *(_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> **)this = param_1;
  return this;
}


/* ==================== _Unique_ptr_base<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_><coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64> @ 180005de9  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > >
   >::_Unique_ptr_base<class coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> > > ><class coco::ConnectionManagerOutputDefault<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64>(class
   coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct types::ImageFrame> > * __ptr64)
   __ptr64 */

_Unique_ptr_base<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Unique_ptr_base<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Unique_ptr_base<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_><coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64>
          (_Unique_ptr_base<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x5de9  170
                       ??$?0PEAV?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Unique_ptr_base@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== _Uninitialized_value_construct_n<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,unsigned___int64,std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_> @ 180005ed9  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 __cdecl
   std::_Uninitialized_value_construct_n<class std::shared_ptr<struct types::ImageFrame> * __ptr64 *
   __ptr64,unsigned __int64,class std::allocator<class std::shared_ptr<struct types::ImageFrame> *
   __ptr64> >(class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,unsigned
   __int64,class std::allocator<class std::shared_ptr<struct types::ImageFrame> * __ptr64> &
   __ptr64) */

shared_ptr<types::ImageFrame> ** __cdecl
std::
_Uninitialized_value_construct_n<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,unsigned___int64,std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_>
          (shared_ptr<struct_types::ImageFrame> **param_1,__uint64 param_2,
          allocator<std::shared_ptr<types::ImageFrame>*___ptr64> *param_3)

{
                    /* 0x5ed9  767
                       ??$_Uninitialized_value_construct_n@PEAPEAV?$shared_ptr@UImageFrame@types@@@std@@_KV?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@YAPEAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAPEAV10@_KAEAV?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@0@@Z
                        */
  memset(param_1,0,param_2 * 8);
  return (shared_ptr<types::ImageFrame> **)(param_1 + param_2);
}


/* ==================== _Fix<std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_> @ 180005f2e  (5 bytes) ==================== */

/* public: static struct royale::DepthData const * __ptr64 && __ptr64 __cdecl
   std::_Select_fixer<struct std::_Ph<1>,0,0,1>::_Fix<class std::tuple<struct royale::DepthData
   const * __ptr64 && __ptr64> >(struct std::_Ph<1> & __ptr64,class std::tuple<struct
   royale::DepthData const * __ptr64 && __ptr64> && __ptr64) */

DepthData ** __cdecl
std::_Select_fixer<std::_Ph<1>,0,0,1>::_Fix<std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_>
          (_Ph<1> *param_1,tuple<royale::DepthData_const*___ptr64&&___ptr64> *param_2)

{
                    /* 0x5f2e  522
                       ??$_Fix@V?$tuple@$$QEAPEBUDepthData@royale@@@std@@@?$_Select_fixer@U?$_Ph@$00@std@@$0A@$0A@$00@std@@SA$$QEAPEBUDepthData@royale@@AEAU?$_Ph@$00@1@$$QEAV?$tuple@$$QEAPEBUDepthData@royale@@@1@@Z
                        */
  return *(DepthData ***)param_2;
}


/* ==================== forward<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_const&___ptr64> @ 180005f97  (5 bytes) ==================== */

/* class std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64> const & __ptr64 __cdecl std::forward<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> const & __ptr64>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> const & __ptr64) */

_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
* __cdecl std::
          forward<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_const&___ptr64>
                    (_Binder<struct_std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(struct_royale::DepthData_const*___ptr64)___ptr64,class_meta::blocks::DeviceStreamBlock*___ptr64,struct_std::_Ph<1>_const&___ptr64>
                     *param_1)

{
                    /* 0x5f97  1139
                       ??$forward@AEBV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@@std@@YAAEBV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@AEBV10@@Z
                        */
  return (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          *)param_1;
}


/* ==================== ~Vector<royale::basicString<char>_> @ 18000603c  (5 bytes) ==================== */

/* public: virtual __cdecl royale::Vector<class royale::basicString<char> >::~Vector<class
   royale::basicString<char> >(void) __ptr64 */

void __thiscall
royale::Vector<royale::basicString<char>_>::~Vector<royale::basicString<char>_>
          (Vector<royale::basicString<char>_> *this)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  
                    /* 0x603c  2101  ??1?$Vector@V?$basicString@D@royale@@@royale@@UEAA@XZ */
  *(undefined ***)this = vftable;
  clear(this);
  freeAllocation(this);
  plVar4 = *(longlong **)(this + 0x10);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}


/* ==================== _Deque_alloc<std::_Deque_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_> @ 180006069  (5 bytes) ==================== */

/* public: __cdecl std::_Deque_alloc<struct std::_Deque_base_types<class std::shared_ptr<struct
   types::ImageFrame>,class std::allocator<class std::shared_ptr<struct types::ImageFrame> > >
   >::_Deque_alloc<struct std::_Deque_base_types<class std::shared_ptr<struct
   types::ImageFrame>,class std::allocator<class std::shared_ptr<struct types::ImageFrame> > >
   >(void) __ptr64 */

_Deque_alloc<std::_Deque_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Deque_alloc<std::_Deque_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Deque_alloc<std::_Deque_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
          (_Deque_alloc<std::_Deque_base_types<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x6069  1576
                       ??0?$_Deque_alloc@U?$_Deque_base_types@V?$shared_ptr@UImageFrame@types@@@std@@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  puVar1 = (undefined8 *)thunk_FUN_180084ee4(0x10);
  if (puVar1 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
    _invalid_parameter_noinfo_noreturn();
  }
  *(undefined8 **)this = puVar1;
  *puVar1 = 0;
  puVar1[1] = 0;
  **(undefined8 **)this = this;
  return this;
}


/* ==================== operator()<royale::DepthData_const*___ptr64> @ 1800060a5  (5 bytes) ==================== */

/* public: void __cdecl std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64>::operator()<struct
   royale::DepthData const * __ptr64>(struct royale::DepthData const * __ptr64 && __ptr64) __ptr64
    */

void __thiscall
std::
_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
::operator()<royale::DepthData_const*___ptr64>
          (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
           *this,DepthData **param_1)

{
                    /* 0x60a5  387
                       ??$?RPEBUDepthData@royale@@@?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@QEAAX$$QEAPEBUDepthData@royale@@@Z
                        */
                    /* WARNING: Could not recover jumptable at 0x000180019f0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)this)(*(undefined8 *)(this + 0x10),*param_1);
  return;
}


/* ==================== ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> @ 1800061c7  (5 bytes) ==================== */

/* public: __cdecl coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> >::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> >(void) __ptr64 */

ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>::
ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x61c7  1447
                       ??0?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@XZ
                        */
  this[8] = (ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>)0x0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined ***)this = vftable;
  *(undefined8 *)(this + 0x28) = 0;
  return this;
}


/* ==================== forward<std::shared_ptr<types::ImageFrame>_> @ 1800061e0  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> && __ptr64 __cdecl std::forward<class
   std::shared_ptr<struct types::ImageFrame> >(class std::shared_ptr<struct types::ImageFrame> &
   __ptr64) */

shared_ptr<types::ImageFrame> * __cdecl
std::forward<std::shared_ptr<types::ImageFrame>_>(shared_ptr<struct_types::ImageFrame> *param_1)

{
                    /* 0x61e0  1244
                       ??$forward@V?$shared_ptr@UImageFrame@types@@@std@@@std@@YA$$QEAV?$shared_ptr@UImageFrame@types@@@0@AEAV10@@Z
                        */
  return (shared_ptr<types::ImageFrame> *)param_1;
}


/* ==================== forward<royale::DepthData_const*___ptr64> @ 1800061ef  (5 bytes) ==================== */

/* struct royale::DepthData const * __ptr64 && __ptr64 __cdecl std::forward<struct royale::DepthData
   const * __ptr64>(struct royale::DepthData const * __ptr64 & __ptr64) */

DepthData ** __cdecl std::forward<royale::DepthData_const*___ptr64>(DepthData **param_1)

{
                    /* 0x61ef  1180
                       ??$forward@PEBUDepthData@royale@@@std@@YA$$QEAPEBUDepthData@royale@@AEAPEBU12@@Z
                        */
  return param_1;
}


/* ==================== destroy<std::shared_ptr<types::ImageFrame>*___ptr64> @ 18000639d  (5 bytes) ==================== */

/* public: static void __cdecl std::_Default_allocator_traits<class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> * __ptr64> >::destroy<class std::shared_ptr<struct
   types::ImageFrame> * __ptr64>(class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> * __ptr64> & __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64
   * __ptr64 const) */

void __cdecl
std::_Default_allocator_traits<std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>_>::
destroy<std::shared_ptr<types::ImageFrame>*___ptr64>
          (allocator<std::shared_ptr<types::ImageFrame>*___ptr64> *param_1,
          shared_ptr<types::ImageFrame> **param_2)

{
                    /* 0x639d  967
                       ??$destroy@PEAV?$shared_ptr@UImageFrame@types@@@std@@@?$_Default_allocator_traits@V?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@SAXAEAV?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@1@QEAPEAV?$shared_ptr@UImageFrame@types@@@1@@Z
                        */
  return;
}


/* ==================== _Fix_arg<meta::blocks::DeviceStreamBlock*___ptr64,std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_> @ 180006410  (5 bytes) ==================== */

/* class meta::blocks::DeviceStreamBlock * __ptr64 & __ptr64 __cdecl std::_Fix_arg<class
   meta::blocks::DeviceStreamBlock * __ptr64,class std::tuple<struct royale::DepthData const *
   __ptr64 && __ptr64> >(class meta::blocks::DeviceStreamBlock * __ptr64 & __ptr64,class
   std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> && __ptr64) */

DeviceStreamBlock ** __cdecl
std::
_Fix_arg<meta::blocks::DeviceStreamBlock*___ptr64,std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_>
          (DeviceStreamBlock **param_1,tuple<royale::DepthData_const*___ptr64&&___ptr64> *param_2)

{
                    /* 0x6410  536
                       ??$_Fix_arg@PEAVDeviceStreamBlock@blocks@meta@@V?$tuple@$$QEAPEBUDepthData@royale@@@std@@@std@@YAAEAPEAVDeviceStreamBlock@blocks@meta@@AEAPEAV123@$$QEAV?$tuple@$$QEAPEBUDepthData@royale@@@0@@Z
                        */
  return param_1;
}


/* ==================== _Fix<std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_> @ 180006532  (5 bytes) ==================== */

/* public: static class meta::blocks::DeviceStreamBlock * __ptr64 & __ptr64 __cdecl
   std::_Select_fixer<class meta::blocks::DeviceStreamBlock * __ptr64,0,0,0>::_Fix<class
   std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> >(class
   meta::blocks::DeviceStreamBlock * __ptr64 & __ptr64,class std::tuple<struct royale::DepthData
   const * __ptr64 && __ptr64> && __ptr64) */

DeviceStreamBlock ** __cdecl
std::_Select_fixer<meta::blocks::DeviceStreamBlock*___ptr64,0,0,0>::
_Fix<std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_>
          (DeviceStreamBlock **param_1,tuple<royale::DepthData_const*___ptr64&&___ptr64> *param_2)

{
                    /* 0x6532  521
                       ??$_Fix@V?$tuple@$$QEAPEBUDepthData@royale@@@std@@@?$_Select_fixer@PEAVDeviceStreamBlock@blocks@meta@@$0A@$0A@$0A@@std@@SAAEAPEAVDeviceStreamBlock@blocks@meta@@AEAPEAV234@$$QEAV?$tuple@$$QEAPEBUDepthData@royale@@@1@@Z
                        */
  return param_1;
}


/* ==================== forward<coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 1800065aa  (5 bytes) ==================== */

/* class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64
   __cdecl std::forward<class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64>(class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64) */

OutputPort<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::forward<coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (OutputPort<class_std::shared_ptr<struct_types::ImageFrame>_> **param_1)

{
                    /* 0x65aa  1083
                       ??$forward@AEAPEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YAAEAPEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (OutputPort<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_> @ 180006654  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::Data<class std::shared_ptr<struct types::ImageFrame>
   >,struct std::default_delete<class coco::Data<class std::shared_ptr<struct types::ImageFrame> > >
   >::unique_ptr<class coco::Data<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::Data<class std::shared_ptr<struct types::ImageFrame> > > >(class
   coco::Data<class std::shared_ptr<struct types::ImageFrame> > * __ptr64) __ptr64 */

unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
::
unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::Data<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,Data<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x6654  1913
                       ??0?$unique_ptr@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(Data<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== _Reset<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_> @ 180006659  (5 bytes) ==================== */

/* protected: void __cdecl std::_Func_class<void,struct royale::DepthData const *
   __ptr64>::_Reset<class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> >(class
   std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64> && __ptr64) __ptr64 */

void __thiscall
std::_Func_class<void,royale::DepthData_const*___ptr64>::
_Reset<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_>
          (_Func_class<void,royale::DepthData_const*___ptr64> *this,
          _Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          *param_1)

{
                    /* 0x6659  619
                       ??$_Reset@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@@?$_Func_class@XPEBUDepthData@royale@@@std@@IEAAX$$QEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@1@@Z
                        */
  *(undefined ***)this =
       _Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
       ::vftable;
  *(undefined8 *)(this + 8) = *(undefined8 *)param_1;
  this[0x10] = *(_Func_class<void,royale::DepthData_const*___ptr64> *)(param_1 + 8);
  *(undefined8 *)(this + 0x18) = *(undefined8 *)(param_1 + 0x10);
  *(_Func_class<void,royale::DepthData_const*___ptr64> **)(this + 0x38) = this;
  return;
}


/* ==================== forward<royale::ICameraDevice*___ptr64&___ptr64> @ 180006758  (5 bytes) ==================== */

/* class royale::ICameraDevice * __ptr64 & __ptr64 __cdecl std::forward<class royale::ICameraDevice
   * __ptr64 & __ptr64>(class royale::ICameraDevice * __ptr64 & __ptr64) */

ICameraDevice ** __cdecl
std::forward<royale::ICameraDevice*___ptr64&___ptr64>(ICameraDevice **param_1)

{
                    /* 0x6758  1087
                       ??$forward@AEAPEAVICameraDevice@royale@@@std@@YAAEAPEAVICameraDevice@royale@@AEAPEAV12@@Z
                        */
  return param_1;
}


/* ==================== forward<std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_> @ 18000677b  (5 bytes) ==================== */

/* struct std::default_delete<class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> > > && __ptr64 __cdecl std::forward<struct std::default_delete<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > > >(struct
   std::default_delete<class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> > > & __ptr64) */

default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_> * __cdecl
std::
forward<std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
          (default_delete<class_coco::ConnectionManagerInputDefault<class_std::shared_ptr<struct_types::ImageFrame>_>_>
           *param_1)

{
                    /* 0x677b  1196
                       ??$forward@U?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@YA$$QEAU?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@0@AEAU10@@Z
                        */
  return (default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>
          *)param_1;
}


/* ==================== forward<RoyaleDataListener*___ptr64&___ptr64> @ 1800067c6  (5 bytes) ==================== */

/* class RoyaleDataListener * __ptr64 & __ptr64 __cdecl std::forward<class RoyaleDataListener *
   __ptr64 & __ptr64>(class RoyaleDataListener * __ptr64 & __ptr64) */

RoyaleDataListener ** __cdecl
std::forward<RoyaleDataListener*___ptr64&___ptr64>(RoyaleDataListener **param_1)

{
                    /* 0x67c6  1090
                       ??$forward@AEAPEAVRoyaleDataListener@@@std@@YAAEAPEAVRoyaleDataListener@@AEAPEAV1@@Z
                        */
  return param_1;
}


/* ==================== _Ptr_copy_cat<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64> @ 18000683e  (5 bytes) ==================== */

/* struct std::_Really_trivial_ptr_iterator_tag __cdecl std::_Ptr_copy_cat<class
   std::shared_ptr<struct types::ImageFrame> * __ptr64,class std::shared_ptr<struct
   types::ImageFrame> * __ptr64>(class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64
   const & __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 const &
   __ptr64) */

shared_ptr<types::ImageFrame> *** __cdecl
std::
_Ptr_copy_cat<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64>
          (shared_ptr<types::ImageFrame> ***param_1,shared_ptr<types::ImageFrame> ***param_2)

{
                    /* 0x683e  576
                       ??$_Ptr_copy_cat@PEAV?$shared_ptr@UImageFrame@types@@@std@@PEAV12@@std@@YA?AU_Really_trivial_ptr_iterator_tag@0@AEBQEAPEAV?$shared_ptr@UImageFrame@types@@@0@0@Z
                        */
  return param_1;
}


/* ==================== _Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_><coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64,coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64,coco::ConnectionPolicy&___ptr64> @ 180006933  (5 bytes) ==================== */

/* public: __cdecl std::_Ref_count_obj<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >::_Ref_count_obj<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > ><class coco::InputPort<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,class coco::OutputPort<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64,struct coco::ConnectionPolicy & __ptr64>(class coco::InputPort<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 && __ptr64,class coco::OutputPort<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64,struct coco::ConnectionPolicy &
   __ptr64) __ptr64 */

_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_><coco::InputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64,coco::OutputPort<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64,coco::ConnectionPolicy&___ptr64>
          (_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *this,
          InputPort<std::shared_ptr<types::ImageFrame>_> **param_1,
          OutputPort<std::shared_ptr<types::ImageFrame>_> **param_2,ConnectionPolicy *param_3)

{
  OutputPort<std::shared_ptr<types::ImageFrame>_> *pOVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
                    /* 0x6933  187
                       ??$?0PEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@1@AEAUConnectionPolicy@1@@?$_Ref_count_obj@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@$$QEAPEAV?$InputPort@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV?$OutputPort@V?$shared_ptr@UImageFrame@types@@@std@@@3@AEAUConnectionPolicy@3@@Z
                        */
  *(undefined4 *)(this + 8) = 1;
  *(undefined4 *)(this + 0xc) = 1;
  *(undefined ***)this = vftable;
  pOVar1 = *param_2;
  uVar2 = *(undefined4 *)param_3;
  uVar3 = *(undefined4 *)(param_3 + 4);
  uVar4 = *(undefined4 *)(param_3 + 8);
  uVar5 = *(undefined4 *)(param_3 + 0xc);
  *(InputPort<std::shared_ptr<types::ImageFrame>_> **)(this + 0x18) = *param_1;
  *(OutputPort<std::shared_ptr<types::ImageFrame>_> **)(this + 0x20) = pOVar1;
  *(undefined4 *)(this + 0x28) = uVar2;
  *(undefined4 *)(this + 0x2c) = uVar3;
  *(undefined4 *)(this + 0x30) = uVar4;
  *(undefined4 *)(this + 0x34) = uVar5;
  *(undefined8 *)(this + 0x38) = 0;
  this[0x40] = (_Ref_count_obj<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>)0x0;
  *(undefined ***)(this + 0x10) =
       coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::vftable;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
  _Mtx_init_in_situ(this + 0x58,2,param_2,param_3,0xfffffffffffffffe);
  _Cnd_init_in_situ(this + 0xa8);
  coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>::CreateConnection
            ((ConnectionTyped<std::shared_ptr<types::ImageFrame>_> *)(this + 0x10));
  return this;
}


/* ==================== _Destroy_range<std::allocator<std::shared_ptr<types::ImageFrame>_>_> @ 1800069ec  (5 bytes) ==================== */

/* void __cdecl std::_Destroy_range<class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> > >(class std::shared_ptr<struct types::ImageFrame> * __ptr64,class
   std::shared_ptr<struct types::ImageFrame> * __ptr64,class std::allocator<class
   std::shared_ptr<struct types::ImageFrame> > & __ptr64) */

void __cdecl
std::_Destroy_range<std::allocator<std::shared_ptr<types::ImageFrame>_>_>
          (shared_ptr<types::ImageFrame> *param_1,shared_ptr<types::ImageFrame> *param_2,
          allocator<std::shared_ptr<types::ImageFrame>_> *param_3)

{
  longlong *plVar1;
  int *piVar2;
  shared_ptr<types::ImageFrame> *psVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  shared_ptr<types::ImageFrame> *psVar7;
  
                    /* 0x69ec  505
                       ??$_Destroy_range@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@YAXPEAV?$shared_ptr@UImageFrame@types@@@0@0AEAV?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@0@@Z
                        */
  if (param_1 != param_2) {
    psVar7 = param_1 + 8;
    do {
      plVar5 = *(longlong **)psVar7;
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar5 + 1;
        lVar6 = *plVar1;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)lVar6 == 1) {
          (**(code **)*plVar5)(plVar5);
          LOCK();
          piVar2 = (int *)((longlong)plVar5 + 0xc);
          iVar4 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar4 == 1) {
            (**(code **)(*plVar5 + 8))(plVar5);
          }
        }
      }
      psVar3 = psVar7 + 8;
      psVar7 = psVar7 + 0x10;
    } while (psVar3 != param_2);
  }
  return;
}


/* ==================== function<void___cdecl(royale::DepthData_const*___ptr64)> @ 180006a96  (5 bytes) ==================== */

/* public: __cdecl std::function<void __cdecl(struct royale::DepthData const *
   __ptr64)>::function<void __cdecl(struct royale::DepthData const * __ptr64)>(class
   std::function<void __cdecl(struct royale::DepthData const * __ptr64)> const & __ptr64) __ptr64 */

function<void___cdecl(royale::DepthData_const*___ptr64)> * __thiscall
std::function<void___cdecl(royale::DepthData_const*___ptr64)>::
function<void___cdecl(royale::DepthData_const*___ptr64)>
          (function<void___cdecl(royale::DepthData_const*___ptr64)> *this,
          function<void___cdecl(struct_royale::DepthData_const*___ptr64)> *param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 in_R8;
  undefined8 in_R9;
  
                    /* 0x6a96  1788
                       ??0?$function@$$A6AXPEBUDepthData@royale@@@Z@std@@QEAA@AEBV01@@Z */
  *(undefined8 *)(this + 0x38) = 0;
  puVar1 = *(undefined8 **)(param_1 + 0x38);
  if (puVar1 != (undefined8 *)0x0) {
    uVar2 = (**(code **)*puVar1)(puVar1,this,in_R8,in_R9,0xfffffffffffffffe);
    *(undefined8 *)(this + 0x38) = uVar2;
  }
  return this;
}


/* ==================== make_unique<RoyaleDataListener,std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void> @ 180006b0e  (5 bytes) ==================== */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* class std::unique_ptr<class RoyaleDataListener,struct std::default_delete<class
   RoyaleDataListener> > __cdecl std::make_unique<class RoyaleDataListener,class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64>,void>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> && __ptr64) */

_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
* __cdecl std::
          make_unique<RoyaleDataListener,std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void>
                    (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
                     *param_1)

{
  _Func_class<void,struct_royale::DepthData_const*___ptr64> *this;
  _Func_class<void,struct_royale::DepthData_const*___ptr64> *p_Var1;
  undefined8 *puVar2;
  undefined8 *in_RDX;
  undefined1 auStack_128 [32];
  undefined ***pppuStack_108;
  undefined **ppuStack_100;
  undefined8 uStack_f8;
  undefined1 uStack_f0;
  undefined8 uStack_e8;
  undefined ***pppuStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  _Func_class<void,struct_royale::DepthData_const*___ptr64> a_Stack_a8 [56];
  _Func_class<void,struct_royale::DepthData_const*___ptr64> *p_Stack_70;
  _Func_class<void,struct_royale::DepthData_const*___ptr64> a_Stack_68 [56];
  _Func_class<void,struct_royale::DepthData_const*___ptr64> *p_Stack_30;
  ulonglong uStack_28;
  
                    /* 0x6b0e  1346
                       ??$make_unique@VRoyaleDataListener@@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@X@std@@YA?AV?$unique_ptr@VRoyaleDataListener@@U?$default_delete@VRoyaleDataListener@@@std@@@0@$$QEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@@Z
                        */
  uStack_c0 = 0xfffffffffffffffe;
  uStack_28 = DAT_1802450f8 ^ (ulonglong)auStack_128;
  puVar2 = (undefined8 *)thunk_FUN_180084ee4(0x48);
  if (puVar2 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
    goto LAB_180023365;
  }
  uStack_f8 = *in_RDX;
  uStack_f0 = *(undefined1 *)(in_RDX + 1);
  uStack_e8 = in_RDX[2];
  ppuStack_100 = _Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
                 ::vftable;
  pppuStack_c8 = &ppuStack_100;
  pppuStack_108 = &ppuStack_100;
  *puVar2 = RoyaleDataListener::vftable;
  this = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)(puVar2 + 1);
  puVar2[8] = 0;
  p_Stack_70 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0;
  puStack_b8 = puVar2;
  if (pppuStack_c8 != (undefined ***)0x0) {
    p_Stack_70 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)
                 (*(code *)_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
                           ::vftable[0])(pppuStack_c8,a_Stack_a8);
  }
  if ((p_Stack_70 == a_Stack_a8) ||
     (p_Var1 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)puVar2[8],
     p_Var1 == this)) {
    p_Stack_30 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0;
    if (p_Stack_70 != (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0) {
      if (p_Stack_70 == a_Stack_a8) {
        p_Stack_30 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)
                     (**(code **)(*(longlong *)p_Stack_70 + 8))(p_Stack_70,a_Stack_68);
        if (p_Stack_70 == (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0)
        goto LAB_1800232f2;
        (**(code **)(*(longlong *)p_Stack_70 + 0x20))
                  (p_Stack_70,CONCAT71((int7)((ulonglong)a_Stack_a8 >> 8),p_Stack_70 != a_Stack_a8))
        ;
      }
      else {
        p_Stack_30 = p_Stack_70;
      }
      p_Stack_70 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0;
    }
LAB_1800232f2:
    _Func_class<void,royale::DepthData_const*___ptr64>::_Reset_move
              ((_Func_class<void,royale::DepthData_const*___ptr64> *)a_Stack_a8,this);
    _Func_class<void,royale::DepthData_const*___ptr64>::_Reset_move
              ((_Func_class<void,royale::DepthData_const*___ptr64> *)this,a_Stack_68);
    if (p_Stack_30 != (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0) {
      (**(code **)(*(longlong *)p_Stack_30 + 0x20))
                (p_Stack_30,CONCAT71((int7)((ulonglong)a_Stack_68 >> 8),p_Stack_30 != a_Stack_68));
      p_Stack_30 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0;
    }
  }
  else {
    puVar2[8] = p_Stack_70;
    p_Stack_70 = p_Var1;
  }
  if (p_Stack_70 != (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0) {
    (**(code **)(*(longlong *)p_Stack_70 + 0x20))
              (p_Stack_70,CONCAT71((int7)((ulonglong)a_Stack_a8 >> 8),p_Stack_70 != a_Stack_a8));
    p_Stack_70 = (_Func_class<void,struct_royale::DepthData_const*___ptr64> *)0x0;
  }
  if (pppuStack_c8 != (undefined ***)0x0) {
    (*(code *)(*pppuStack_c8)[4])
              (pppuStack_c8,
               CONCAT71((int7)((ulonglong)&ppuStack_100 >> 8),pppuStack_c8 != &ppuStack_100));
  }
LAB_180023365:
  *(undefined8 **)param_1 = puVar2;
  return param_1;
}


/* ==================== move<std::shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>&___ptr64> @ 180006bdb  (5 bytes) ==================== */

/* class std::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct types::ImageFrame>
   > > && __ptr64 __cdecl std::move<class std::shared_ptr<class coco::ConnectionTyped<class
   std::shared_ptr<struct types::ImageFrame> > > & __ptr64>(class std::shared_ptr<class
   coco::ConnectionTyped<class std::shared_ptr<struct types::ImageFrame> > > & __ptr64) */

shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> * __cdecl
std::move<std::shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>&___ptr64>
          (shared_ptr<class_coco::ConnectionTyped<class_std::shared_ptr<struct_types::ImageFrame>_>_>
           *param_1)

{
                    /* 0x6bdb  1389
                       ??$move@AEAV?$shared_ptr@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@YA$$QEAV?$shared_ptr@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@0@AEAV10@@Z
                        */
  return (shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *)param_1;
}


/* ==================== _Fix_arg<std::_Ph<1>,std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_> @ 180006be5  (5 bytes) ==================== */

/* struct royale::DepthData const * __ptr64 && __ptr64 __cdecl std::_Fix_arg<struct
   std::_Ph<1>,class std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> >(struct
   std::_Ph<1> & __ptr64,class std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> &&
   __ptr64) */

DepthData ** __cdecl
std::_Fix_arg<std::_Ph<1>,std::tuple<royale::DepthData_const*___ptr64&&___ptr64>_>
          (_Ph<1> *param_1,tuple<royale::DepthData_const*___ptr64&&___ptr64> *param_2)

{
                    /* 0x6be5  543
                       ??$_Fix_arg@U?$_Ph@$00@std@@V?$tuple@$$QEAPEBUDepthData@royale@@@2@@std@@YA$$QEAPEBUDepthData@royale@@AEAU?$_Ph@$00@0@$$QEAV?$tuple@$$QEAPEBUDepthData@royale@@@0@@Z
                        */
  return *(DepthData ***)param_2;
}


/* ==================== _Tuple_val<royale::DepthData_const*___ptr64&&___ptr64><royale::DepthData_const*___ptr64> @ 180006bf9  (5 bytes) ==================== */

/* public: __cdecl std::_Tuple_val<struct royale::DepthData const * __ptr64 &&
   __ptr64>::_Tuple_val<struct royale::DepthData const * __ptr64 && __ptr64><struct
   royale::DepthData const * __ptr64>(struct royale::DepthData const * __ptr64 && __ptr64) __ptr64
    */

_Tuple_val<royale::DepthData_const*___ptr64&&___ptr64> * __thiscall
std::_Tuple_val<royale::DepthData_const*___ptr64&&___ptr64>::
_Tuple_val<royale::DepthData_const*___ptr64&&___ptr64><royale::DepthData_const*___ptr64>
          (_Tuple_val<royale::DepthData_const*___ptr64&&___ptr64> *this,DepthData **param_1)

{
                    /* 0x6bf9  200
                       ??$?0PEBUDepthData@royale@@@?$_Tuple_val@$$QEAPEBUDepthData@royale@@@std@@QEAA@$$QEAPEBUDepthData@royale@@@Z
                        */
  *(DepthData ***)this = param_1;
  return this;
}


/* ==================== ~Data<std::shared_ptr<types::ImageFrame>_> @ 180006ccb  (5 bytes) ==================== */

/* public: virtual __cdecl coco::Data<class std::shared_ptr<struct types::ImageFrame> >::~Data<class
   std::shared_ptr<struct types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::Data<std::shared_ptr<types::ImageFrame>_>::~Data<std::shared_ptr<types::ImageFrame>_>
          (Data<std::shared_ptr<types::ImageFrame>_> *this)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  
                    /* 0x6ccb  2081  ??1?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ
                        */
  plVar4 = *(longlong **)(this + 0x120);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  std::vector<unsigned___int64,std::allocator<unsigned___int64>_>::_Tidy
            ((vector<unsigned___int64,std::allocator<unsigned___int64>_> *)(this + 0x100));
  std::
  deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
  ::
  ~deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
            ((deque<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::allocator<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>
              *)(this + 0x10));
  return;
}


/* ==================== ~_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_> @ 180006d8e  (5 bytes) ==================== */

/* public: __cdecl std::_Deque_iterator<class std::_Deque_val<struct std::_Deque_simple_types<class
   std::shared_ptr<struct types::ImageFrame> > > >::~_Deque_iterator<class std::_Deque_val<struct
   std::_Deque_simple_types<class std::shared_ptr<struct types::ImageFrame> > > >(void) __ptr64 */

void __thiscall
std::
_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>::
~_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
          (_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
                    /* 0x6d8e  2129
                       ??1?$_Deque_iterator@V?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@@std@@QEAA@XZ
                        */
  return;
}


/* ==================== _Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_> @ 180006ece  (5 bytes) ==================== */

/* public: __cdecl std::_Vector_val<struct std::_Simple_types<class std::shared_ptr<struct
   types::ImageFrame> > >::_Vector_val<struct std::_Simple_types<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

_Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::_Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_>::
_Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_>
          (_Vector_val<std::_Simple_types<std::shared_ptr<types::ImageFrame>_>_> *this)

{
                    /* 0x6ece  1735
                       ??0?$_Vector_val@U?$_Simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  return this;
}


/* ==================== forward<royale::DepthData_const*___ptr64&&___ptr64> @ 180007004  (5 bytes) ==================== */

/* struct royale::DepthData const * __ptr64 && __ptr64 __cdecl std::forward<struct royale::DepthData
   const * __ptr64 && __ptr64>(struct royale::DepthData const * __ptr64 & __ptr64) */

DepthData ** __cdecl std::forward<royale::DepthData_const*___ptr64&&___ptr64>(DepthData **param_1)

{
                    /* 0x7004  1017
                       ??$forward@$$QEAPEBUDepthData@royale@@@std@@YA$$QEAPEBUDepthData@royale@@AEAPEBU12@@Z
                        */
  return param_1;
}


/* ==================== addressof<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_> @ 180007090  (5 bytes) ==================== */

/* class std::_Deque_val<struct std::_Deque_simple_types<class std::shared_ptr<struct
   types::ImageFrame> > > * __ptr64 __cdecl std::addressof<class std::_Deque_val<struct
   std::_Deque_simple_types<class std::shared_ptr<struct types::ImageFrame> > > >(class
   std::_Deque_val<struct std::_Deque_simple_types<class std::shared_ptr<struct types::ImageFrame> >
   > & __ptr64) */

_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_> * __cdecl
std::addressof<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
          (_Deque_val<struct_std::_Deque_simple_types<class_std::shared_ptr<struct_types::ImageFrame>_>_>
           *param_1)

{
                    /* 0x7090  857
                       ??$addressof@V?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@@std@@YAPEAV?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@0@AEAV10@@Z
                        */
  return (_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_> *)param_1;
}


/* ==================== ~ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_> @ 1800070a9  (5 bytes) ==================== */

/* public: virtual __cdecl coco::ConnectionManagerOutput<class std::shared_ptr<struct
   types::ImageFrame> >::~ConnectionManagerOutput<class std::shared_ptr<struct types::ImageFrame>
   >(void) __ptr64 */

void __thiscall
coco::ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_>::
~ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerOutput<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x70a9  2051
                       ??1?$ConnectionManagerOutput@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ
                        */
  std::
  vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
  ::_Tidy((vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
           *)(this + 0x10));
  return;
}


/* ==================== _Unchecked<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64> @ 180007121  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 __cdecl std::_Unchecked<class
   std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64>(class std::shared_ptr<struct
   types::ImageFrame> * __ptr64 * __ptr64) */

shared_ptr<types::ImageFrame> ** __cdecl
std::_Unchecked<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64>
          (shared_ptr<struct_types::ImageFrame> **param_1)

{
                    /* 0x7121  686
                       ??$_Unchecked@PEAPEAV?$shared_ptr@UImageFrame@types@@@std@@@std@@YAPEAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAPEAV10@@Z
                        */
  return (shared_ptr<types::ImageFrame> **)param_1;
}


/* ==================== make_unique<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,int&___ptr64,void> @ 180007180  (5 bytes) ==================== */

/* class std::unique_ptr<class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame>
   >,struct std::default_delete<class coco::CircularBuffer<class std::shared_ptr<struct
   types::ImageFrame> > > > __cdecl std::make_unique<class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> >,int & __ptr64,void>(int & __ptr64) */

int * __cdecl
std::make_unique<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,int&___ptr64,void>
          (int *param_1)

{
  undefined8 *puVar1;
  int iVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  int *in_RDX;
  
                    /* 0x7180  1321
                       ??$make_unique@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAHX@std@@YA?AV?$unique_ptr@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@0@AEAH@Z
                        */
  puVar3 = (undefined8 *)thunk_FUN_180084ee4(0x148);
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    iVar2 = *in_RDX;
    *puVar3 = coco::BufferBase<std::shared_ptr<types::ImageFrame>_>::vftable;
    *(undefined4 *)(puVar3 + 1) = 0;
    *(undefined1 *)((longlong)puVar3 + 0xc) = 0;
    coco::ConnectionStatisticsBuilder::ConnectionStatisticsBuilder
              ((ConnectionStatisticsBuilder *)(puVar3 + 2));
    *puVar3 = coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>::vftable;
    puVar1 = puVar3 + 0x23;
    *puVar1 = 0;
    puVar3[0x24] = 0;
    puVar3[0x25] = 0;
    puVar3[0x26] = 0;
    puVar3[0x27] = 0;
    puVar4 = (undefined8 *)thunk_FUN_180084ee4(0x10);
    if (puVar4 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    *puVar1 = puVar4;
    *puVar4 = 0;
    puVar4[1] = 0;
    *(undefined8 **)*puVar1 = puVar1;
    puVar3[0x28] = (longlong)iVar2;
    puVar3[7] = (longlong)iVar2;
    puVar3[0x13] = 0x7ff0000000000000;
    puVar3[0x1b] = 0x7ff0000000000000;
    puVar3[0x1e] = 0;
    puVar3[8] = 0;
    puVar3[9] = 0;
    puVar3[0xe] = 0;
    puVar3[0xf] = 0;
    coco::ConnectionStatisticsBuilder::ResetProducerStats
              ((ConnectionStatisticsBuilder *)(puVar3 + 2));
    puVar3[0x10] = 0x7ff0000000000000;
  }
  *(undefined8 **)param_1 = puVar3;
  return param_1;
}


/* ==================== Mono0FrameGrabber @ 1800071f8  (5 bytes) ==================== */

/* private: void __cdecl meta::blocks::DeviceStreamBlock::Mono0FrameGrabber(class
   std::shared_ptr<struct sdc::ImageData> const & __ptr64) __ptr64 */

void __thiscall
meta::blocks::DeviceStreamBlock::Mono0FrameGrabber
          (DeviceStreamBlock *this,shared_ptr<sdc::ImageData> *param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  shared_ptr<sdc::ImageData> asStack_20 [8];
  longlong *plStack_18;
  
                    /* 0x71f8  3117
                       ?Mono0FrameGrabber@DeviceStreamBlock@blocks@meta@@AEAAXAEBV?$shared_ptr@UImageData@sdc@@@std@@@Z
                        */
  CreateMonoImage(this,asStack_20);
  (**(code **)(**(longlong **)(this + 0x2b8) + 8))(*(longlong **)(this + 0x2b8),asStack_20);
  if (plStack_18 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_18 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_18)(plStack_18);
      LOCK();
      piVar2 = (int *)((longlong)plStack_18 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plStack_18 + 8))(plStack_18);
      }
    }
  }
  return;
}


/* ==================== shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> @ 180007202  (5 bytes) ==================== */

/* public: __cdecl std::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >::shared_ptr<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
          (shared_ptr<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *this)

{
                    /* 0x7202  1835
                       ??0?$shared_ptr@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  return this;
}


/* ==================== ~_Ref_count_obj<types::ImageFrame> @ 180007284  (5 bytes) ==================== */

/* public: virtual __cdecl std::_Ref_count_obj<struct types::ImageFrame>::~_Ref_count_obj<struct
   types::ImageFrame>(void) __ptr64 */

void __thiscall
std::_Ref_count_obj<types::ImageFrame>::~_Ref_count_obj<types::ImageFrame>
          (_Ref_count_obj<types::ImageFrame> *this)

{
                    /* 0x7284  2179  ??1?$_Ref_count_obj@UImageFrame@types@@@std@@UEAA@XZ */
  *(undefined ***)this = _Ref_count_base::vftable;
  return;
}


/* ==================== _Call<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64&___ptr64,royale::DepthData_const*___ptr64> @ 1800072c0  (5 bytes) ==================== */

/* public: static void __cdecl std::_Invoker_pmf_pointer::_Call<void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64 & __ptr64,struct royale::DepthData const *
   __ptr64>(void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64 & __ptr64,struct
   royale::DepthData const * __ptr64 && __ptr64) */

void __cdecl
std::_Invoker_pmf_pointer::
_Call<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64&___ptr64,royale::DepthData_const*___ptr64>
          (_func_void_DepthData_ptr *param_1,DeviceStreamBlock **param_2,DepthData **param_3)

{
                    /* 0x72c0  438
                       ??$_Call@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZAEAPEAV123@PEBU45@@_Invoker_pmf_pointer@std@@SAXP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZAEAPEAV234@$$QEAPEBU56@@Z
                        */
                    /* WARNING: Could not recover jumptable at 0x00018001a82c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*param_1)((DepthData *)*param_2);
  return;
}


/* ==================== _Func_base<void,royale::DepthData_const*___ptr64> @ 180007301  (5 bytes) ==================== */

/* public: __cdecl std::_Func_base<void,struct royale::DepthData const *
   __ptr64>::_Func_base<void,struct royale::DepthData const * __ptr64>(void) __ptr64 */

_Func_base<void,royale::DepthData_const*___ptr64> * __thiscall
std::_Func_base<void,royale::DepthData_const*___ptr64>::
_Func_base<void,royale::DepthData_const*___ptr64>
          (_Func_base<void,royale::DepthData_const*___ptr64> *this)

{
                    /* 0x7301  1609  ??0?$_Func_base@XPEBUDepthData@royale@@@std@@QEAA@XZ */
  *(undefined ***)this = vftable;
  return this;
}


/* ==================== _Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>,std::_Iterator_base0> @ 18000737e  (5 bytes) ==================== */

/* public: __cdecl std::_Tree_unchecked_const_iterator<class std::_Tree_val<struct
   std::_Tree_simple_types<struct std::pair<unsigned int const ,struct sdc::TofConfig> > >,struct
   std::_Iterator_base0>::_Tree_unchecked_const_iterator<class std::_Tree_val<struct
   std::_Tree_simple_types<struct std::pair<unsigned int const ,struct sdc::TofConfig> > >,struct
   std::_Iterator_base0>(struct std::_Tree_node<struct std::pair<unsigned int const ,struct
   sdc::TofConfig>,void * __ptr64> * __ptr64,class std::_Tree_val<struct
   std::_Tree_simple_types<struct std::pair<unsigned int const ,struct sdc::TofConfig> > > const *
   __ptr64) __ptr64 */

_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>,std::_Iterator_base0>
* __thiscall
std::
_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>,std::_Iterator_base0>
::
_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>,std::_Iterator_base0>
          (_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>,std::_Iterator_base0>
           *this,_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> *param_1,
          _Tree_val<std::_Tree_simple_types<std::pair<unsigned_int_const_,sdc::TofConfig>_>_>
          *param_2)

{
                    /* 0x737e  1716
                       ??0?$_Tree_unchecked_const_iterator@V?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBIUTofConfig@sdc@@@std@@@std@@@std@@U_Iterator_base0@2@@std@@QEAA@PEAU?$_Tree_node@U?$pair@$$CBIUTofConfig@sdc@@@std@@PEAX@1@PEBV?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBIUTofConfig@sdc@@@std@@@std@@@1@@Z
                        */
  *(_Tree_node<std::pair<unsigned_int_const_,sdc::TofConfig>,void*___ptr64> **)this = param_1;
  return this;
}


/* ==================== default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_><coco::Buffer<std::shared_ptr<types::ImageFrame>_>,void> @ 1800073c4  (5 bytes) ==================== */

/* public: __cdecl std::default_delete<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> > >::default_delete<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> > ><class coco::Buffer<class std::shared_ptr<struct types::ImageFrame>
   >,void>(struct std::default_delete<class coco::Buffer<class std::shared_ptr<struct
   types::ImageFrame> > > const & __ptr64) __ptr64 */

default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>::
default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_><coco::Buffer<std::shared_ptr<types::ImageFrame>_>,void>
          (default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_> *this,
          default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_> *param_1)

{
                    /* 0x73c4  223
                       ??$?0V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@X@?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@AEBU?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@1@@Z
                        */
  return this;
}


/* ==================== forward<coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 18000747d  (5 bytes) ==================== */

/* class coco::Data<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64 __cdecl
   std::forward<class coco::Data<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64>(class coco::Data<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64)
    */

Data<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::forward<coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (Data<class_std::shared_ptr<struct_types::ImageFrame>_> **param_1)

{
                    /* 0x747d  1072
                       ??$forward@AEAPEAV?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YAAEAPEAV?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (Data<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== operator=<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>,void> @ 1800074ff  (5 bytes) ==================== */

/* public: class std::unique_ptr<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> > > > & __ptr64 __cdecl std::unique_ptr<class
   coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > >
   >::operator=<class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >
   >,void>(class std::unique_ptr<class coco::CircularBuffer<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::CircularBuffer<class
   std::shared_ptr<struct types::ImageFrame> > > > && __ptr64) __ptr64 */

unique_ptr<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>,struct_std::default_delete<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
::
operator=<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>,void>
          (unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,unique_ptr<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
                 *param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
                    /* 0x74ff  328
                       ??$?4V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@X@?$unique_ptr@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAAAEAV01@$$QEAV?$unique_ptr@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@1@@Z
                        */
  uVar1 = *(undefined8 *)param_1;
  *(undefined8 *)param_1 = 0;
  puVar2 = *(undefined8 **)this;
  *(undefined8 *)this = uVar1;
  if (puVar2 != (undefined8 *)0x0) {
    (**(code **)*puVar2)(puVar2,1);
  }
  return (unique_ptr<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>,struct_std::default_delete<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>_>_>
          *)this;
}


/* ==================== addressof<std::unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_>_> @ 180007504  (5 bytes) ==================== */

/* class std::unique_ptr<class royale::ICameraDevice,struct std::default_delete<class
   royale::ICameraDevice> > * __ptr64 __cdecl std::addressof<class std::unique_ptr<class
   royale::ICameraDevice,struct std::default_delete<class royale::ICameraDevice> > >(class
   std::unique_ptr<class royale::ICameraDevice,struct std::default_delete<class
   royale::ICameraDevice> > & __ptr64) */

unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_> * __cdecl
std::addressof<std::unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_>_>
          (unique_ptr<class_royale::ICameraDevice,struct_std::default_delete<class_royale::ICameraDevice>_>
           *param_1)

{
                    /* 0x7504  881
                       ??$addressof@V?$unique_ptr@VICameraDevice@royale@@U?$default_delete@VICameraDevice@royale@@@std@@@std@@@std@@YAPEAV?$unique_ptr@VICameraDevice@royale@@U?$default_delete@VICameraDevice@royale@@@std@@@0@AEAV10@@Z
                        */
  return (unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_> *)param_1;
}


/* ==================== _Unique_ptr_base<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_><royale::ICameraDevice*___ptr64> @ 180007513  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class royale::ICameraDevice,struct
   std::default_delete<class royale::ICameraDevice> >::_Unique_ptr_base<class
   royale::ICameraDevice,struct std::default_delete<class royale::ICameraDevice> ><class
   royale::ICameraDevice * __ptr64>(class royale::ICameraDevice * __ptr64) __ptr64 */

_Unique_ptr_base<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_> * __thiscall
std::_Unique_ptr_base<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_>::
_Unique_ptr_base<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_><royale::ICameraDevice*___ptr64>
          (_Unique_ptr_base<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_> *this
          ,ICameraDevice *param_1)

{
                    /* 0x7513  191
                       ??$?0PEAVICameraDevice@royale@@@?$_Unique_ptr_base@VICameraDevice@royale@@U?$default_delete@VICameraDevice@royale@@@std@@@std@@QEAA@PEAVICameraDevice@royale@@@Z
                        */
  *(ICameraDevice **)this = param_1;
  return this;
}


/* ==================== _Unique_ptr_base<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_><coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64> @ 18000756d  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> > > >::_Unique_ptr_base<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > > ><class
   coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > * __ptr64>(class
   coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > * __ptr64) __ptr64 */

_Unique_ptr_base<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Unique_ptr_base<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Unique_ptr_base<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_><coco::BufferBase<std::shared_ptr<types::ImageFrame>_>*___ptr64>
          (_Unique_ptr_base<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,BufferBase<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x756d  153
                       ??$?0PEAV?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Unique_ptr_base@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(BufferBase<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== forward<coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180007590  (5 bytes) ==================== */

/* class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64 __cdecl
   std::forward<class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64>(class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64) */

Buffer<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::forward<coco::Buffer<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (Buffer<class_std::shared_ptr<struct_types::ImageFrame>_> **param_1)

{
                    /* 0x7590  1037
                       ??$forward@AEAPEAV?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YAAEAPEAV?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (Buffer<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== default_delete<coco::ConnectionManager><coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,void> @ 180007626  (5 bytes) ==================== */

/* public: __cdecl std::default_delete<class coco::ConnectionManager>::default_delete<class
   coco::ConnectionManager><class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> >,void>(struct std::default_delete<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > > const &
   __ptr64) __ptr64 */

default_delete<coco::ConnectionManager> * __thiscall
std::default_delete<coco::ConnectionManager>::
default_delete<coco::ConnectionManager><coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,void>
          (default_delete<coco::ConnectionManager> *this,
          default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>
          *param_1)

{
                    /* 0x7626  246
                       ??$?0V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@X@?$default_delete@VConnectionManager@coco@@@std@@QEAA@AEBU?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@1@@Z
                        */
  return this;
}


/* ==================== _Compressed_pair<std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180007635  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > >,class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,1>::_Compressed_pair<struct std::default_delete<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > >,class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64,1><class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> > * __ptr64 & __ptr64>(struct std::_Zero_then_variadic_args_t,class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > * __ptr64
   & __ptr64) __ptr64 */

_Compressed_pair<std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
* __thiscall
std::
_Compressed_pair<std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
::
_Compressed_pair<std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>,coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x7635  57
                       ??$?0AEAPEAV?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Compressed_pair@U?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@PEAV?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAV?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== forward<std::default_delete<royale::ICameraDevice>_> @ 1800076bc  (5 bytes) ==================== */

/* struct std::default_delete<class royale::ICameraDevice> && __ptr64 __cdecl std::forward<struct
   std::default_delete<class royale::ICameraDevice> >(struct std::default_delete<class
   royale::ICameraDevice> & __ptr64) */

default_delete<royale::ICameraDevice> * __cdecl
std::forward<std::default_delete<royale::ICameraDevice>_>
          (default_delete<class_royale::ICameraDevice> *param_1)

{
                    /* 0x76bc  1216
                       ??$forward@U?$default_delete@VICameraDevice@royale@@@std@@@std@@YA$$QEAU?$default_delete@VICameraDevice@royale@@@0@AEAU10@@Z
                        */
  return (default_delete<royale::ICameraDevice> *)param_1;
}


/* ==================== addressof<std::pair<unsigned_int_const_,sdc::TofConfig>_> @ 18000774d  (5 bytes) ==================== */

/* struct std::pair<unsigned int const ,struct sdc::TofConfig> * __ptr64 __cdecl
   std::addressof<struct std::pair<unsigned int const ,struct sdc::TofConfig> >(struct
   std::pair<unsigned int const ,struct sdc::TofConfig> & __ptr64) */

pair<unsigned_int_const_,sdc::TofConfig> * __cdecl
std::addressof<std::pair<unsigned_int_const_,sdc::TofConfig>_>
          (pair<unsigned_int_const_,struct_sdc::TofConfig> *param_1)

{
                    /* 0x774d  838
                       ??$addressof@U?$pair@$$CBIUTofConfig@sdc@@@std@@@std@@YAPEAU?$pair@$$CBIUTofConfig@sdc@@@0@AEAU10@@Z
                        */
  return (pair<unsigned_int_const_,sdc::TofConfig> *)param_1;
}


/* ==================== emplace_back<std::shared_ptr<types::ImageFrame>_const&___ptr64> @ 18000780b  (5 bytes) ==================== */

/* public: void __cdecl std::vector<class std::shared_ptr<struct types::ImageFrame>,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> > >::emplace_back<class
   std::shared_ptr<struct types::ImageFrame> const & __ptr64>(class std::shared_ptr<struct
   types::ImageFrame> const & __ptr64) __ptr64 */

void __thiscall
std::vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
::emplace_back<std::shared_ptr<types::ImageFrame>_const&___ptr64>
          (vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
           *this,shared_ptr<types::ImageFrame> *param_1)

{
  ulonglong uVar1;
  _Ptr_base<types::ImageFrame> *p_Var2;
  _Ref_count_base *p_Var3;
  ImageFrame *pIVar4;
  ulonglong uVar5;
  shared_ptr<types::ImageFrame> *psVar6;
  longlong lVar7;
  undefined1 uStackX_18;
  longlong lVar8;
  shared_ptr<types::ImageFrame> *psVar9;
  undefined8 uVar10;
  
                    /* 0x780b  1009
                       ??$emplace_back@AEBV?$shared_ptr@UImageFrame@types@@@std@@@?$vector@V?$shared_ptr@UImageFrame@types@@@std@@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@QEAAXAEBV?$shared_ptr@UImageFrame@types@@@1@@Z
                        */
  uVar10 = 0xfffffffffffffffe;
  p_Var2 = *(_Ptr_base<types::ImageFrame> **)(this + 8);
  if (*(_Ptr_base<types::ImageFrame> **)(this + 0x10) == p_Var2) {
    lVar7 = (longlong)p_Var2 - *(longlong *)this >> 4;
    if (lVar7 == 0xfffffffffffffff) {
      _Xlength();
      return;
    }
    uVar1 = lVar7 + 1;
    uVar5 = (longlong)*(_Ptr_base<types::ImageFrame> **)(this + 0x10) - *(longlong *)this >> 4;
    if (0xfffffffffffffff - (uVar5 >> 1) < uVar5) {
      uVar5 = uVar1;
    }
    else {
      uVar5 = (uVar5 >> 1) + uVar5;
      if (uVar5 < uVar1) {
        uVar5 = uVar1;
      }
    }
    lVar8 = lVar7;
    psVar6 = allocator<std::shared_ptr<types::ImageFrame>_>::allocate
                       ((allocator<std::shared_ptr<types::ImageFrame>_> *)this,uVar5);
    p_Var2 = (_Ptr_base<types::ImageFrame> *)(psVar6 + lVar7 * 0x10);
    *(undefined8 *)p_Var2 = 0;
    *(undefined8 *)(p_Var2 + 8) = 0;
    p_Var3 = *(_Ref_count_base **)(param_1 + 8);
    pIVar4 = *(ImageFrame **)param_1;
    if (p_Var3 != (_Ref_count_base *)0x0) {
      LOCK();
      *(int *)(p_Var3 + 8) = *(int *)(p_Var3 + 8) + 1;
      UNLOCK();
    }
    psVar9 = psVar6;
    _Ptr_base<types::ImageFrame>::_Reset0(p_Var2,pIVar4,p_Var3);
    _Uninitialized_move_al_unchecked<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
              (*(undefined8 *)this,*(undefined8 *)(this + 8),psVar6,this,0,uStackX_18,lVar8,psVar9,
               uVar10);
    _Change_array(this,psVar6,uVar1,uVar5);
  }
  else {
    *(undefined8 *)p_Var2 = 0;
    *(undefined8 *)(p_Var2 + 8) = 0;
    p_Var3 = *(_Ref_count_base **)(param_1 + 8);
    pIVar4 = *(ImageFrame **)param_1;
    if (p_Var3 != (_Ref_count_base *)0x0) {
      LOCK();
      *(int *)(p_Var3 + 8) = *(int *)(p_Var3 + 8) + 1;
      UNLOCK();
    }
    _Ptr_base<types::ImageFrame>::_Reset0(p_Var2,pIVar4,p_Var3);
    *(longlong *)(this + 8) = *(longlong *)(this + 8) + 0x10;
  }
  return;
}


/* ==================== unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_> @ 180007833  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class royale::ICameraDevice,struct std::default_delete<class
   royale::ICameraDevice> >::unique_ptr<class royale::ICameraDevice,struct std::default_delete<class
   royale::ICameraDevice> >(void) __ptr64 */

unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_> * __thiscall
std::unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_>::
unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_>
          (unique_ptr<royale::ICameraDevice,std::default_delete<royale::ICameraDevice>_> *this)

{
                    /* 0x7833  1915
                       ??0?$unique_ptr@VICameraDevice@royale@@U?$default_delete@VICameraDevice@royale@@@std@@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  return this;
}


/* ==================== _Ref_count_obj<types::ImageFrame><> @ 1800078a6  (5 bytes) ==================== */

/* public: __cdecl std::_Ref_count_obj<struct types::ImageFrame>::_Ref_count_obj<struct
   types::ImageFrame><>(void) __ptr64 */

_Ref_count_obj<types::ImageFrame> * __thiscall
std::_Ref_count_obj<types::ImageFrame>::_Ref_count_obj<types::ImageFrame><>
          (_Ref_count_obj<types::ImageFrame> *this)

{
                    /* 0x78a6  17  ??$?0$$V@?$_Ref_count_obj@UImageFrame@types@@@std@@QEAA@XZ */
  *(undefined4 *)(this + 8) = 1;
  *(undefined4 *)(this + 0xc) = 1;
  *(undefined ***)this = vftable;
  memset((ImageFrame *)(this + 0x10),0,0xb8);
  types::ImageFrame::ImageFrame((ImageFrame *)(this + 0x10));
  return this;
}


/* ==================== _Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> @ 1800078d3  (5 bytes) ==================== */

/* public: __cdecl std::_Ptr_base<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >::_Ptr_base<class coco::ConnectionTyped<class std::shared_ptr<struct
   types::ImageFrame> > >(void) __ptr64 */

_Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> * __thiscall
std::_Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>::
_Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_>
          (_Ptr_base<coco::ConnectionTyped<std::shared_ptr<types::ImageFrame>_>_> *this)

{
                    /* 0x78d3  1659
                       ??0?$_Ptr_base@V?$ConnectionTyped@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@QEAA@XZ
                        */
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  return this;
}


/* ==================== _Copy_memmove<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64*___ptr64> @ 180007955  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 __cdecl
   std::_Copy_memmove<class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64,class
   std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64>(class std::shared_ptr<struct
   types::ImageFrame> * __ptr64 * __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64
   * __ptr64,class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64) */

shared_ptr<types::ImageFrame> ** __cdecl
std::
_Copy_memmove<std::shared_ptr<types::ImageFrame>*___ptr64*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64*___ptr64>
          (shared_ptr<struct_types::ImageFrame> **param_1,
          shared_ptr<struct_types::ImageFrame> **param_2,
          shared_ptr<struct_types::ImageFrame> **param_3)

{
                    /* 0x7955  459
                       ??$_Copy_memmove@PEAPEAV?$shared_ptr@UImageFrame@types@@@std@@PEAPEAV12@@std@@YAPEAPEAV?$shared_ptr@UImageFrame@types@@@0@PEAPEAV10@00@Z
                        */
  memmove(param_3,param_1,(longlong)param_2 - (longlong)param_1);
  return (shared_ptr<types::ImageFrame> **)
         (((longlong)param_2 - (longlong)param_1) + (longlong)param_3);
}


/* ==================== forward<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 18000797d  (5 bytes) ==================== */

/* class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > *
   __ptr64 & __ptr64 __cdecl std::forward<class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64>(class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > * __ptr64 &
   __ptr64) */

ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> ** __cdecl
std::
forward<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (ConnectionManagerInputDefault<class_std::shared_ptr<struct_types::ImageFrame>_> **param_1
          )

{
                    /* 0x797d  1054
                       ??$forward@AEAPEAV?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@YAAEAPEAV?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@AEAPEAV12@@Z
                        */
  return (ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_> **)param_1;
}


/* ==================== invoke<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64,royale::DepthData_const*___ptr64> @ 180007991  (5 bytes) ==================== */

/* void __cdecl std::invoke<class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> & __ptr64,struct
   royale::DepthData const * __ptr64>(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> & __ptr64,struct
   royale::DepthData const * __ptr64 && __ptr64) */

void __cdecl
std::
invoke<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>&___ptr64,royale::DepthData_const*___ptr64>
          (_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
           *param_1,DepthData **param_2)

{
                    /* 0x7991  1291
                       ??$invoke@AEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@PEBUDepthData@royale@@@std@@YAXAEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@$$QEAPEBUDepthData@royale@@@Z
                        */
                    /* WARNING: Could not recover jumptable at 0x000180020f3a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)param_1)(*(undefined8 *)(param_1 + 0x10),*param_2);
  return;
}


/* ==================== _Reset_impl<std::_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>,std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_> @ 1800079e1  (5 bytes) ==================== */

/* protected: void __cdecl std::_Func_class<void,struct royale::DepthData const *
   __ptr64>::_Reset_impl<class std::_Func_impl_no_alloc<class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64>,void,struct royale::DepthData const * __ptr64>,class std::_Binder<struct
   std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const *
   __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const &
   __ptr64> >(class std::_Binder<struct std::_Unforced,void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64> && __ptr64,struct
   std::integral_constant<bool,0>) __ptr64 */

void __thiscall
std::_Func_class<void,royale::DepthData_const*___ptr64>::
_Reset_impl<std::_Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>,std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>_>
          (_Func_class<void,royale::DepthData_const*___ptr64> *this,undefined8 *param_1)

{
                    /* 0x79e1  631
                       ??$_Reset_impl@V?$_Func_impl_no_alloc@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@std@@XPEBUDepthData@royale@@@std@@V?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@2@@?$_Func_class@XPEBUDepthData@royale@@@std@@IEAAX$$QEAV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@1@U?$integral_constant@_N$0A@@1@@Z
                        */
  *(undefined ***)this =
       _Func_impl_no_alloc<std::_Binder<std::_Unforced,void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>,void,royale::DepthData_const*___ptr64>
       ::vftable;
  *(undefined8 *)(this + 8) = *param_1;
  this[0x10] = *(_Func_class<void,royale::DepthData_const*___ptr64> *)(param_1 + 1);
  *(undefined8 *)(this + 0x18) = param_1[2];
  *(_Func_class<void,royale::DepthData_const*___ptr64> **)(this + 0x38) = this;
  return;
}


/* ==================== ~unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_> @ 180007a27  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class royale::IDepthDataListener,struct std::default_delete<class
   royale::IDepthDataListener> >::~unique_ptr<class royale::IDepthDataListener,struct
   std::default_delete<class royale::IDepthDataListener> >(void) __ptr64 */

void __thiscall
std::unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>::
~unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>
          (unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x7a27  2377
                       ??1?$unique_ptr@VIDepthDataListener@royale@@U?$default_delete@VIDepthDataListener@royale@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000180031280. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== _Unique_ptr_base<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_><coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64> @ 180007a86  (5 bytes) ==================== */

/* public: __cdecl std::_Unique_ptr_base<class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > >
   >::_Unique_ptr_base<class coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> > > ><class coco::ConnectionManagerOutputScatter<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64>(class
   coco::ConnectionManagerOutputScatter<class std::shared_ptr<struct types::ImageFrame> > * __ptr64)
   __ptr64 */

_Unique_ptr_base<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
* __thiscall
std::
_Unique_ptr_base<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
::
_Unique_ptr_base<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_><coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>*___ptr64>
          (_Unique_ptr_base<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x7a86  176
                       ??$?0PEAV?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Unique_ptr_base@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@PEAV?$ConnectionManagerOutputScatter@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(ConnectionManagerOutputScatter<std::shared_ptr<types::ImageFrame>_> **)this = param_1;
  return this;
}


/* ==================== default_delete<royale::IDepthDataListener><RoyaleDataListener,void> @ 180007aae  (5 bytes) ==================== */

/* public: __cdecl std::default_delete<class royale::IDepthDataListener>::default_delete<class
   royale::IDepthDataListener><class RoyaleDataListener,void>(struct std::default_delete<class
   RoyaleDataListener> const & __ptr64) __ptr64 */

default_delete<royale::IDepthDataListener> * __thiscall
std::default_delete<royale::IDepthDataListener>::
default_delete<royale::IDepthDataListener><RoyaleDataListener,void>
          (default_delete<royale::IDepthDataListener> *this,
          default_delete<RoyaleDataListener> *param_1)

{
                    /* 0x7aae  306
                       ??$?0VRoyaleDataListener@@X@?$default_delete@VIDepthDataListener@royale@@@std@@QEAA@AEBU?$default_delete@VRoyaleDataListener@@@1@@Z
                        */
  return this;
}


/* ==================== _Compressed_pair<std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>,coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64> @ 180007b99  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<struct std::default_delete<class coco::Data<class
   std::shared_ptr<struct types::ImageFrame> > >,class coco::Data<class std::shared_ptr<struct
   types::ImageFrame> > * __ptr64,1>::_Compressed_pair<struct std::default_delete<class
   coco::Data<class std::shared_ptr<struct types::ImageFrame> > >,class coco::Data<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64,1><class coco::Data<class
   std::shared_ptr<struct types::ImageFrame> > * __ptr64 & __ptr64>(struct
   std::_Zero_then_variadic_args_t,class coco::Data<class std::shared_ptr<struct types::ImageFrame>
   > * __ptr64 & __ptr64) __ptr64 */

_Compressed_pair<std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>,coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
* __thiscall
std::
_Compressed_pair<std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>,coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
::
_Compressed_pair<std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>,coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64,1><coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64&___ptr64>
          (_Compressed_pair<std::default_delete<coco::Data<std::shared_ptr<types::ImageFrame>_>_>,coco::Data<std::shared_ptr<types::ImageFrame>_>*___ptr64,1>
           *this,undefined8 param_2,undefined8 *param_3)

{
                    /* 0x7b99  63
                       ??$?0AEAPEAV?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@?$_Compressed_pair@U?$default_delete@V?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@PEAV?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@$00@std@@QEAA@U_Zero_then_variadic_args_t@1@AEAPEAV?$Data@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@Z
                        */
  *(undefined8 *)this = *param_3;
  return this;
}


/* ==================== ~shared_ptr<types::ImageFrame> @ 180007bc1  (5 bytes) ==================== */

/* public: __cdecl std::shared_ptr<struct types::ImageFrame>::~shared_ptr<struct
   types::ImageFrame>(void) __ptr64 */

void __thiscall
std::shared_ptr<types::ImageFrame>::~shared_ptr<types::ImageFrame>
          (shared_ptr<types::ImageFrame> *this)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  
                    /* 0x7bc1  2305  ??1?$shared_ptr@UImageFrame@types@@@std@@QEAA@XZ */
  plVar4 = *(longlong **)(this + 8);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}


/* ==================== CreateImuFrame @ 180007bcb  (5 bytes) ==================== */

/* private: void __cdecl meta::blocks::DeviceStreamBlock::CreateImuFrame(class
   std::shared_ptr<struct sdc::RawImuData> const & __ptr64,struct types::MatrixStamped<short,3,1> *
   __ptr64,struct types::MatrixStamped<short,3,1> * __ptr64)const __ptr64 */

void __thiscall
meta::blocks::DeviceStreamBlock::CreateImuFrame
          (DeviceStreamBlock *this,shared_ptr<sdc::RawImuData> *param_1,
          MatrixStamped<short,3,1> *param_2,MatrixStamped<short,3,1> *param_3)

{
  short *psVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  __uint64 _Var5;
  double dVar6;
  longlong alStack_28 [4];
  
                    /* 0x7bcb  3021
                       ?CreateImuFrame@DeviceStreamBlock@blocks@meta@@AEBAXAEBV?$shared_ptr@URawImuData@sdc@@@std@@PEAU?$MatrixStamped@F$02$00@types@@1@Z
                        */
  dVar6 = device::Meta2TimestampToSeconds(*(undefined8 *)(*(longlong *)param_1 + 0x20));
  lVar2 = _Query_perf_frequency();
  lVar3 = _Query_perf_counter();
  psVar1 = *(short **)param_1;
  lVar4 = (lVar3 % lVar2) * 1000000000;
  lVar3 = lVar4 / lVar2 + (lVar3 / lVar2) * 1000000000;
  if (*psVar1 != 0) {
    *(short *)(param_2 + 0x58) = psVar1[1];
    *(short *)(param_2 + 0x5a) = psVar1[2];
    *(short *)(param_2 + 0x5c) = psVar1[3];
    *(double *)(param_2 + 8) = dVar6;
    _Var5 = device::Meta2FrameIdToUint64(*(undefined8 *)(*(longlong *)param_1 + 0x28),lVar4 % lVar2)
    ;
    *(__uint64 *)param_2 = _Var5;
    std::
    unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
    ::
    _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
              ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
                *)(param_2 + 0x10),
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)alStack_28);
    *(longlong *)(alStack_28[0] + 0x30) = lVar3;
  }
  lVar2 = *(longlong *)param_1;
  if (*(short *)(lVar2 + 8) != 0) {
    *(undefined2 *)(param_3 + 0x58) = *(undefined2 *)(lVar2 + 10);
    *(undefined2 *)(param_3 + 0x5a) = *(undefined2 *)(lVar2 + 0xc);
    *(undefined2 *)(param_3 + 0x5c) = *(undefined2 *)(lVar2 + 0xe);
    *(double *)(param_3 + 8) = dVar6;
    _Var5 = device::Meta2FrameIdToUint64(*(undefined8 *)(*(longlong *)param_1 + 0x28));
    *(__uint64 *)param_3 = _Var5;
    std::
    unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
    ::
    _Try_emplace<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const&___ptr64>
              ((unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000>_>_>_>_>_>
                *)(param_3 + 0x10),
               (basic_string<char,std::char_traits<char>,std::allocator<char>_> *)alStack_28);
    *(longlong *)(alStack_28[0] + 0x30) = lVar3;
  }
  return;
}


/* ==================== forward<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64> @ 180007c5c  (5 bytes) ==================== */

/* void (__cdecl meta::blocks::DeviceStreamBlock::*&& __ptr64 __cdecl std::forward<void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64>(void
   (__cdecl meta::blocks::DeviceStreamBlock::*& __ptr64)(struct royale::DepthData const * __ptr64)
   __ptr64))(struct royale::DepthData const * __ptr64) __ptr64 */

void____cdecl_meta__blocks__DeviceStreamBlock________ptr64__royale__DepthData_const____ptr64____ptr64
* __cdecl std::
          forward<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64>
                    (_func_void_DepthData_ptr **param_1)

{
                    /* 0x7c5c  1166
                       ??$forward@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@Z@std@@YA$$QEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZAEAP8123@EAAX0@Z@Z
                        */
  return (void____cdecl_meta__blocks__DeviceStreamBlock________ptr64__royale__DepthData_const____ptr64____ptr64
          *)param_1;
}


/* ==================== forward<std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_> @ 180007c8e  (5 bytes) ==================== */

/* struct std::default_delete<class coco::CircularBuffer<class std::shared_ptr<struct
   types::ImageFrame> > > && __ptr64 __cdecl std::forward<struct std::default_delete<class
   coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> > > >(struct
   std::default_delete<class coco::CircularBuffer<class std::shared_ptr<struct types::ImageFrame> >
   > & __ptr64) */

default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_> * __cdecl
std::forward<std::default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_>_>
          (default_delete<class_coco::CircularBuffer<class_std::shared_ptr<struct_types::ImageFrame>_>_>
           *param_1)

{
                    /* 0x7c8e  1191
                       ??$forward@U?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@YA$$QEAU?$default_delete@V?$CircularBuffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@0@AEAU10@@Z
                        */
  return (default_delete<coco::CircularBuffer<std::shared_ptr<types::ImageFrame>_>_> *)param_1;
}


/* ==================== forward_as_tuple<royale::DepthData_const*___ptr64> @ 180007c98  (5 bytes) ==================== */

/* class std::tuple<struct royale::DepthData const * __ptr64 && __ptr64> __cdecl
   std::forward_as_tuple<struct royale::DepthData const * __ptr64>(struct royale::DepthData const *
   __ptr64 && __ptr64) */

DepthData ** __cdecl std::forward_as_tuple<royale::DepthData_const*___ptr64>(DepthData **param_1)

{
  DepthData *in_RDX;
  
                    /* 0x7c98  1258
                       ??$forward_as_tuple@PEBUDepthData@royale@@@std@@YA?AV?$tuple@$$QEAPEBUDepthData@royale@@@0@$$QEAPEBUDepthData@royale@@@Z
                        */
  *param_1 = in_RDX;
  return param_1;
}


/* ==================== bind<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64> @ 180007ddd  (5 bytes) ==================== */

/* class std::_Binder<struct std::_Unforced,void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64,struct
   std::_Ph<1> const & __ptr64> __cdecl std::bind<void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64>(void (__cdecl
   meta::blocks::DeviceStreamBlock::*&& __ptr64)(struct royale::DepthData const * __ptr64)
   __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64 && __ptr64,struct std::_Ph<1> const &
   __ptr64) */

void____cdecl_meta__blocks__DeviceStreamBlock________ptr64__royale__DepthData_const____ptr64____ptr64
* __cdecl std::
          bind<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
                    (void____cdecl_meta__blocks__DeviceStreamBlock________ptr64__royale__DepthData_const____ptr64____ptr64
                     *param_1,DeviceStreamBlock **param_2,_Ph<1> *param_3)

{
                    /* 0x7ddd  894
                       ??$bind@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV123@AEBU?$_Ph@$00@std@@@std@@YA?AV?$_Binder@U_Unforced@std@@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV345@AEBU?$_Ph@$00@2@@0@$$QEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@Z$$QEAPEAV234@AEBU?$_Ph@$00@0@@Z
                        */
  *(DeviceStreamBlock **)param_1 = *param_2;
  *(undefined8 *)(param_1 + 0x10) = *(undefined8 *)param_3;
  return param_1;
}


/* ==================== forward<std::shared_ptr<types::ImageFrame>_const&___ptr64> @ 180007ee1  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> const & __ptr64 __cdecl std::forward<class
   std::shared_ptr<struct types::ImageFrame> const & __ptr64>(class std::shared_ptr<struct
   types::ImageFrame> const & __ptr64) */

shared_ptr<types::ImageFrame> * __cdecl
std::forward<std::shared_ptr<types::ImageFrame>_const&___ptr64>
          (shared_ptr<struct_types::ImageFrame> *param_1)

{
                    /* 0x7ee1  1156
                       ??$forward@AEBV?$shared_ptr@UImageFrame@types@@@std@@@std@@YAAEBV?$shared_ptr@UImageFrame@types@@@0@AEBV10@@Z
                        */
  return (shared_ptr<types::ImageFrame> *)param_1;
}


/* ==================== _Emplace_back_with_unused_capacity<std::shared_ptr<types::ImageFrame>_const&___ptr64> @ 180007f36  (5 bytes) ==================== */

/* private: void __cdecl std::vector<class std::shared_ptr<struct types::ImageFrame>,class
   std::allocator<class std::shared_ptr<struct types::ImageFrame> >
   >::_Emplace_back_with_unused_capacity<class std::shared_ptr<struct types::ImageFrame> const &
   __ptr64>(class std::shared_ptr<struct types::ImageFrame> const & __ptr64) __ptr64 */

void __thiscall
std::vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
::_Emplace_back_with_unused_capacity<std::shared_ptr<types::ImageFrame>_const&___ptr64>
          (vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
           *this,shared_ptr<types::ImageFrame> *param_1)

{
  _Ptr_base<types::ImageFrame> *this_00;
  _Ref_count_base *p_Var1;
  ImageFrame *pIVar2;
  
                    /* 0x7f36  513
                       ??$_Emplace_back_with_unused_capacity@AEBV?$shared_ptr@UImageFrame@types@@@std@@@?$vector@V?$shared_ptr@UImageFrame@types@@@std@@V?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@2@@std@@AEAAXAEBV?$shared_ptr@UImageFrame@types@@@1@@Z
                        */
  this_00 = *(_Ptr_base<types::ImageFrame> **)(this + 8);
  *(undefined8 *)this_00 = 0;
  *(undefined8 *)(this_00 + 8) = 0;
  p_Var1 = *(_Ref_count_base **)(param_1 + 8);
  pIVar2 = *(ImageFrame **)param_1;
  if (p_Var1 != (_Ref_count_base *)0x0) {
    LOCK();
    *(int *)(p_Var1 + 8) = *(int *)(p_Var1 + 8) + 1;
    UNLOCK();
  }
  _Ptr_base<types::ImageFrame>::_Reset0(this_00,pIVar2,p_Var1);
  *(longlong *)(this + 8) = *(longlong *)(this + 8) + 0x10;
  return;
}


/* ==================== operator=<RoyaleDataListener,std::default_delete<RoyaleDataListener>,void> @ 180007f86  (5 bytes) ==================== */

/* public: class std::unique_ptr<class royale::IDepthDataListener,struct std::default_delete<class
   royale::IDepthDataListener> > & __ptr64 __cdecl std::unique_ptr<class
   royale::IDepthDataListener,struct std::default_delete<class royale::IDepthDataListener>
   >::operator=<class RoyaleDataListener,struct std::default_delete<class
   RoyaleDataListener>,void>(class std::unique_ptr<class RoyaleDataListener,struct
   std::default_delete<class RoyaleDataListener> > && __ptr64) __ptr64 */

unique_ptr<class_royale::IDepthDataListener,struct_std::default_delete<class_royale::IDepthDataListener>_>
* __thiscall
std::unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>::
operator=<RoyaleDataListener,std::default_delete<RoyaleDataListener>,void>
          (unique_ptr<royale::IDepthDataListener,std::default_delete<royale::IDepthDataListener>_>
           *this,unique_ptr<RoyaleDataListener,std::default_delete<RoyaleDataListener>_> *param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
                    /* 0x7f86  354
                       ??$?4VRoyaleDataListener@@U?$default_delete@VRoyaleDataListener@@@std@@X@?$unique_ptr@VIDepthDataListener@royale@@U?$default_delete@VIDepthDataListener@royale@@@std@@@std@@QEAAAEAV01@$$QEAV?$unique_ptr@VRoyaleDataListener@@U?$default_delete@VRoyaleDataListener@@@std@@@1@@Z
                        */
  uVar1 = *(undefined8 *)param_1;
  *(undefined8 *)param_1 = 0;
  puVar2 = *(undefined8 **)this;
  *(undefined8 *)this = uVar1;
  if (puVar2 != (undefined8 *)0x0) {
    (**(code **)*puVar2)(puVar2,1);
  }
  return (unique_ptr<class_royale::IDepthDataListener,struct_std::default_delete<class_royale::IDepthDataListener>_>
          *)this;
}


/* ==================== ~IDepthDataListener @ 180007fcc  (5 bytes) ==================== */

/* public: virtual __cdecl royale::IDepthDataListener::~IDepthDataListener(void) __ptr64 */

void __thiscall royale::IDepthDataListener::~IDepthDataListener(IDepthDataListener *this)

{
                    /* 0x7fcc  2412  ??1IDepthDataListener@royale@@UEAA@XZ */
  *(undefined ***)this = vftable;
  return;
}


/* ==================== Data_RegisterNewBogus0Frame @ 180007fef  (5 bytes) ==================== */

/* public: virtual enum sdc::EventHandlerStatus __cdecl
   sdc::EventHandlerAdapter::Data_RegisterNewBogus0Frame(class std::function<void __cdecl(class
   std::shared_ptr<struct sdc::ImageData> const & __ptr64)>) __ptr64 */

EventHandlerStatus __thiscall
sdc::EventHandlerAdapter::Data_RegisterNewBogus0Frame(undefined8 param_1,longlong *param_2)

{
  longlong *plVar1;
  
                    /* 0x7fef  3031
                       ?Data_RegisterNewBogus0Frame@EventHandlerAdapter@sdc@@UEAA?AW4EventHandlerStatus@2@V?$function@$$A6AXAEBV?$shared_ptr@UImageData@sdc@@@std@@@Z@std@@@Z
                        */
  plVar1 = (longlong *)param_2[7];
  if (plVar1 != (longlong *)0x0) {
    (**(code **)(*plVar1 + 0x20))(plVar1,plVar1 != param_2);
    param_2[7] = 0;
  }
  return 0;
}


/* ==================== ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> @ 180007ff4  (5 bytes) ==================== */

/* public: __cdecl coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> >::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> >(void) __ptr64 */

ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> * __thiscall
coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>::
ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x7ff4  1459
                       ??0?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@QEAA@XZ
                        */
  this[8] = (ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>)0x0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined ***)this = vftable;
  return this;
}


/* ==================== _Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0><void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64> @ 180008030  (5 bytes) ==================== */

/* public: __cdecl std::_Compressed_pair<void (__cdecl meta::blocks::DeviceStreamBlock::*)(struct
   royale::DepthData const * __ptr64) __ptr64,class std::tuple<class meta::blocks::DeviceStreamBlock
   * __ptr64,struct std::_Ph<1> >,0>::_Compressed_pair<void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   std::tuple<class meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> >,0><void (__cdecl
   meta::blocks::DeviceStreamBlock::*)(struct royale::DepthData const * __ptr64) __ptr64,class
   meta::blocks::DeviceStreamBlock * __ptr64,struct std::_Ph<1> const & __ptr64>(struct
   std::_One_then_variadic_args_t,void (__cdecl meta::blocks::DeviceStreamBlock::*&& __ptr64)(struct
   royale::DepthData const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64 &&
   __ptr64,struct std::_Ph<1> const & __ptr64) __ptr64 */

_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
* __thiscall
std::
_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
::
_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0><void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_const&___ptr64>
          (_Compressed_pair<void_(__cdecl_meta::blocks::DeviceStreamBlock::*)(royale::DepthData_const*___ptr64)___ptr64,std::tuple<meta::blocks::DeviceStreamBlock*___ptr64,std::_Ph<1>_>,0>
           *this,undefined8 param_2,undefined8 *param_3,undefined8 *param_4)

{
                    /* 0x8030  137
                       ??$?0P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZPEAV012@AEBU?$_Ph@$00@std@@@?$_Compressed_pair@P8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZV?$tuple@PEAVDeviceStreamBlock@blocks@meta@@U?$_Ph@$00@std@@@std@@$0A@@std@@QEAA@U_One_then_variadic_args_t@1@$$QEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@Z$$QEAPEAV345@AEBU?$_Ph@$00@1@@Z
                        */
  *(undefined8 *)this = *param_3;
  *(undefined8 *)(this + 0x10) = *param_4;
  return this;
}


/* ==================== allocator<std::shared_ptr<types::ImageFrame>*___ptr64><std::shared_ptr<types::ImageFrame>_> @ 18000808f  (5 bytes) ==================== */

/* public: __cdecl std::allocator<class std::shared_ptr<struct types::ImageFrame> *
   __ptr64>::allocator<class std::shared_ptr<struct types::ImageFrame> * __ptr64><class
   std::shared_ptr<struct types::ImageFrame> >(class std::allocator<class std::shared_ptr<struct
   types::ImageFrame> > const & __ptr64) __ptr64 */

allocator<std::shared_ptr<types::ImageFrame>*___ptr64> * __thiscall
std::allocator<std::shared_ptr<types::ImageFrame>*___ptr64>::
allocator<std::shared_ptr<types::ImageFrame>*___ptr64><std::shared_ptr<types::ImageFrame>_>
          (allocator<std::shared_ptr<types::ImageFrame>*___ptr64> *this,
          allocator<std::shared_ptr<types::ImageFrame>_> *param_1)

{
                    /* 0x808f  299
                       ??$?0V?$shared_ptr@UImageFrame@types@@@std@@@?$allocator@PEAV?$shared_ptr@UImageFrame@types@@@std@@@std@@QEAA@AEBV?$allocator@V?$shared_ptr@UImageFrame@types@@@std@@@1@@Z
                        */
  return this;
}


/* ==================== ~unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_> @ 1800080a3  (5 bytes) ==================== */

/* public: __cdecl std::unique_ptr<class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> >,struct std::default_delete<class
   coco::ConnectionManagerInputDefault<class std::shared_ptr<struct types::ImageFrame> > >
   >::~unique_ptr<class coco::ConnectionManagerInputDefault<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::ConnectionManagerInputDefault<class
   std::shared_ptr<struct types::ImageFrame> > > >(void) __ptr64 */

void __thiscall
std::
unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
::
~unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
          (unique_ptr<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::ConnectionManagerInputDefault<std::shared_ptr<types::ImageFrame>_>_>_>
           *this)

{
  undefined8 *puVar1;
  
                    /* 0x80a3  2354
                       ??1?$unique_ptr@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$ConnectionManagerInputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAA@XZ
                        */
  puVar1 = *(undefined8 **)this;
  if (puVar1 == (undefined8 *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000180071f80. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*puVar1)(puVar1,1);
  return;
}


/* ==================== operator=<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>,void> @ 1800080bc  (5 bytes) ==================== */

/* public: class std::unique_ptr<class coco::BufferBase<class std::shared_ptr<struct
   types::ImageFrame> >,struct std::default_delete<class coco::BufferBase<class
   std::shared_ptr<struct types::ImageFrame> > > > & __ptr64 __cdecl std::unique_ptr<class
   coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::BufferBase<class std::shared_ptr<struct types::ImageFrame> > >
   >::operator=<class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> >,struct
   std::default_delete<class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> >
   >,void>(class std::unique_ptr<class coco::Buffer<class std::shared_ptr<struct types::ImageFrame>
   >,struct std::default_delete<class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> >
   > > && __ptr64) __ptr64 */

unique_ptr<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>,struct_std::default_delete<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>_>_>
* __thiscall
std::
unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
::
operator=<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>,void>
          (unique_ptr<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::BufferBase<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,unique_ptr<coco::Buffer<std::shared_ptr<types::ImageFrame>_>,std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
                 *param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
                    /* 0x80bc  322
                       ??$?4V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@X@?$unique_ptr@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$BufferBase@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@QEAAAEAV01@$$QEAV?$unique_ptr@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@U?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@1@@Z
                        */
  uVar1 = *(undefined8 *)param_1;
  *(undefined8 *)param_1 = 0;
  puVar2 = *(undefined8 **)this;
  *(undefined8 *)this = uVar1;
  if (puVar2 != (undefined8 *)0x0) {
    (**(code **)*puVar2)(puVar2,1);
  }
  return (unique_ptr<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>,struct_std::default_delete<class_coco::BufferBase<class_std::shared_ptr<struct_types::ImageFrame>_>_>_>
          *)this;
}


/* ==================== addressof<std::shared_ptr<types::ImageFrame>*___ptr64> @ 180008134  (5 bytes) ==================== */

/* class std::shared_ptr<struct types::ImageFrame> * __ptr64 * __ptr64 __cdecl std::addressof<class
   std::shared_ptr<struct types::ImageFrame> * __ptr64>(class std::shared_ptr<struct
   types::ImageFrame> * __ptr64 & __ptr64) */

shared_ptr<types::ImageFrame> ** __cdecl
std::addressof<std::shared_ptr<types::ImageFrame>*___ptr64>
          (shared_ptr<struct_types::ImageFrame> **param_1)

{
                    /* 0x8134  827
                       ??$addressof@PEAV?$shared_ptr@UImageFrame@types@@@std@@@std@@YAPEAPEAV?$shared_ptr@UImageFrame@types@@@0@AEAPEAV10@@Z
                        */
  return (shared_ptr<types::ImageFrame> **)param_1;
}


/* ==================== forward<std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_> @ 180008161  (5 bytes) ==================== */

/* struct std::default_delete<class coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > >
   && __ptr64 __cdecl std::forward<struct std::default_delete<class coco::Buffer<class
   std::shared_ptr<struct types::ImageFrame> > > >(struct std::default_delete<class
   coco::Buffer<class std::shared_ptr<struct types::ImageFrame> > > & __ptr64) */

default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_> * __cdecl
std::forward<std::default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_>_>
          (default_delete<class_coco::Buffer<class_std::shared_ptr<struct_types::ImageFrame>_>_>
           *param_1)

{
                    /* 0x8161  1185
                       ??$forward@U?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@std@@@std@@YA$$QEAU?$default_delete@V?$Buffer@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@@0@AEAU10@@Z
                        */
  return (default_delete<coco::Buffer<std::shared_ptr<types::ImageFrame>_>_> *)param_1;
}


/* ==================== _Deque_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_> @ 1800081e8  (5 bytes) ==================== */

/* public: __cdecl std::_Deque_iterator<class std::_Deque_val<struct std::_Deque_simple_types<class
   std::shared_ptr<struct types::ImageFrame> > > >::_Deque_iterator<class std::_Deque_val<struct
   std::_Deque_simple_types<class std::shared_ptr<struct types::ImageFrame> > > >(unsigned
   __int64,struct std::_Container_base12 const * __ptr64) __ptr64 */

_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_> *
__thiscall
std::
_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>::
_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
          (_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<std::shared_ptr<types::ImageFrame>_>_>_>
           *this,__uint64 param_1,_Container_base12 *param_2)

{
                    /* 0x81e8  1590
                       ??0?$_Deque_iterator@V?$_Deque_val@U?$_Deque_simple_types@V?$shared_ptr@UImageFrame@types@@@std@@@std@@@std@@@std@@QEAA@_KPEBU_Container_base12@1@@Z
                        */
  *(__uint64 *)(this + 0x10) = param_1;
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  if (param_2 != (_Container_base12 *)0x0) {
    *(undefined8 *)this = *(undefined8 *)param_2;
  }
  return this;
}


/* ==================== ImageFrame @ 18000837d  (5 bytes) ==================== */

/* public: __cdecl types::ImageFrame::ImageFrame(void) __ptr64 */

ImageFrame * __thiscall types::ImageFrame::ImageFrame(ImageFrame *this)

{
                    /* 0x837d  1948  ??0ImageFrame@types@@QEAA@XZ */
  Header::Header((Header *)this);
  *(undefined8 *)(this + 0x58) = 0x42ff0000;
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 100) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined8 *)(this + 0x88) = 0;
  *(undefined8 *)(this + 0x90) = 0;
  *(ImageFrame **)(this + 0x98) = this + 0x60;
  *(ImageFrame **)(this + 0xa0) = this + 0xa8;
  *(undefined8 *)(this + 0xb0) = 0;
  **(undefined8 **)(this + 0xa0) = 0;
  return this;
}


/* ==================== Pair<royale::ProcessingFlag,royale::Variant> @ 18000839b  (5 bytes) ==================== */

/* public: __cdecl royale::Pair<enum royale::ProcessingFlag,class royale::Variant>::Pair<enum
   royale::ProcessingFlag,class royale::Variant>(class royale::Pair<enum
   royale::ProcessingFlag,class royale::Variant> && __ptr64) __ptr64 */

Pair<royale::ProcessingFlag,royale::Variant> * __thiscall
royale::Pair<royale::ProcessingFlag,royale::Variant>::Pair<royale::ProcessingFlag,royale::Variant>
          (Pair<royale::ProcessingFlag,royale::Variant> *this,
          Pair<enum_royale::ProcessingFlag,class_royale::Variant> *param_1)

{
  undefined8 uVar1;
  
                    /* 0x839b  1512
                       ??0?$Pair@W4ProcessingFlag@royale@@VVariant@2@@royale@@QEAA@$$QEAV01@@Z */
  *(undefined ***)this = vftable;
  *(undefined4 *)(this + 8) = *(undefined4 *)(param_1 + 8);
  uVar1 = *(undefined8 *)(param_1 + 0x14);
  *(undefined8 *)(this + 0xc) = *(undefined8 *)(param_1 + 0xc);
  *(undefined8 *)(this + 0x14) = uVar1;
  *(undefined8 *)(this + 0x1c) = *(undefined8 *)(param_1 + 0x1c);
  return this;
}


/* ==================== forward<royale::Variant> @ 1800083c8  (5 bytes) ==================== */

/* class royale::Variant && __ptr64 __cdecl std::forward<class royale::Variant>(class
   royale::Variant & __ptr64) */

Variant * __cdecl std::forward<royale::Variant>(Variant *param_1)

{
                    /* 0x83c8  1248
                       ??$forward@VVariant@royale@@@std@@YA$$QEAVVariant@royale@@AEAV12@@Z */
  return param_1;
}


/* ==================== ~ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> @ 1800083dc  (5 bytes) ==================== */

/* public: virtual __cdecl coco::ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> >::~ConnectionManagerOutputDefault<class std::shared_ptr<struct
   types::ImageFrame> >(void) __ptr64 */

void __thiscall
coco::ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>::
~ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_>
          (ConnectionManagerOutputDefault<std::shared_ptr<types::ImageFrame>_> *this)

{
                    /* 0x83dc  2057
                       ??1?$ConnectionManagerOutputDefault@V?$shared_ptr@UImageFrame@types@@@std@@@coco@@UEAA@XZ
                        */
  std::
  vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
  ::_Tidy((vector<std::shared_ptr<coco::ConnectionBase>,std::allocator<std::shared_ptr<coco::ConnectionBase>_>_>
           *)(this + 0x10));
  return;
}


/* ==================== _Call<void_(__cdecl_meta::blocks::DeviceStreamBlock::*&___ptr64)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64&___ptr64,royale::DepthData_const*___ptr64> @ 18000841d  (5 bytes) ==================== */

/* public: static void __cdecl std::_Invoker_ret<struct std::_Unforced,0>::_Call<void (__cdecl
   meta::blocks::DeviceStreamBlock::*& __ptr64)(struct royale::DepthData const * __ptr64)
   __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64 & __ptr64,struct royale::DepthData const
   * __ptr64>(void (__cdecl meta::blocks::DeviceStreamBlock::*& __ptr64)(struct royale::DepthData
   const * __ptr64) __ptr64,class meta::blocks::DeviceStreamBlock * __ptr64 & __ptr64,struct
   royale::DepthData const * __ptr64 && __ptr64) */

void __cdecl
std::_Invoker_ret<std::_Unforced,0>::
_Call<void_(__cdecl_meta::blocks::DeviceStreamBlock::*&___ptr64)(royale::DepthData_const*___ptr64)___ptr64,meta::blocks::DeviceStreamBlock*___ptr64&___ptr64,royale::DepthData_const*___ptr64>
          (_func_void_DepthData_ptr **param_1,DeviceStreamBlock **param_2,DepthData **param_3)

{
                    /* 0x841d  408
                       ??$_Call@AEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZAEAPEAV123@PEBU45@@?$_Invoker_ret@U_Unforced@std@@$0A@@std@@SAXAEAP8DeviceStreamBlock@blocks@meta@@EAAXPEBUDepthData@royale@@@ZAEAPEAV234@$$QEAPEBU56@@Z
                        */
                    /* WARNING: Could not recover jumptable at 0x00018001a3ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**param_1)((DepthData *)*param_2);
  return;
}


/* ==================== emplace_back<std::shared_ptr<types::ImageFrame>_const&___ptr64> @ 18007a4c0  (5 bytes) ==================== */

void __thiscall
std::vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
::emplace_back<std::shared_ptr<types::ImageFrame>_const&___ptr64>
          (vector<std::shared_ptr<types::ImageFrame>,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
           *this,shared_ptr<types::ImageFrame> *param_1)

{
  ulonglong uVar1;
  _Ptr_base<types::ImageFrame> *p_Var2;
  _Ref_count_base *p_Var3;
  ImageFrame *pIVar4;
  ulonglong uVar5;
  shared_ptr<types::ImageFrame> *psVar6;
  longlong lVar7;
  undefined1 uStackX_18;
  longlong lVar8;
  shared_ptr<types::ImageFrame> *psVar9;
  undefined8 uVar10;
  
  uVar10 = 0xfffffffffffffffe;
  p_Var2 = *(_Ptr_base<types::ImageFrame> **)(this + 8);
  if (*(_Ptr_base<types::ImageFrame> **)(this + 0x10) == p_Var2) {
    lVar7 = (longlong)p_Var2 - *(longlong *)this >> 4;
    if (lVar7 == 0xfffffffffffffff) {
      _Xlength();
      return;
    }
    uVar1 = lVar7 + 1;
    uVar5 = (longlong)*(_Ptr_base<types::ImageFrame> **)(this + 0x10) - *(longlong *)this >> 4;
    if (0xfffffffffffffff - (uVar5 >> 1) < uVar5) {
      uVar5 = uVar1;
    }
    else {
      uVar5 = (uVar5 >> 1) + uVar5;
      if (uVar5 < uVar1) {
        uVar5 = uVar1;
      }
    }
    lVar8 = lVar7;
    psVar6 = allocator<std::shared_ptr<types::ImageFrame>_>::allocate
                       ((allocator<std::shared_ptr<types::ImageFrame>_> *)this,uVar5);
    p_Var2 = (_Ptr_base<types::ImageFrame> *)(psVar6 + lVar7 * 0x10);
    *(undefined8 *)p_Var2 = 0;
    *(undefined8 *)(p_Var2 + 8) = 0;
    p_Var3 = *(_Ref_count_base **)(param_1 + 8);
    pIVar4 = *(ImageFrame **)param_1;
    if (p_Var3 != (_Ref_count_base *)0x0) {
      LOCK();
      *(int *)(p_Var3 + 8) = *(int *)(p_Var3 + 8) + 1;
      UNLOCK();
    }
    psVar9 = psVar6;
    _Ptr_base<types::ImageFrame>::_Reset0(p_Var2,pIVar4,p_Var3);
    _Uninitialized_move_al_unchecked<std::shared_ptr<types::ImageFrame>*___ptr64,std::shared_ptr<struct_types::ImageFrame>*___ptr64,std::allocator<std::shared_ptr<types::ImageFrame>_>_>
              (*(undefined8 *)this,*(undefined8 *)(this + 8),psVar6,this,0,uStackX_18,lVar8,psVar9,
               uVar10);
    _Change_array(this,psVar6,uVar1,uVar5);
  }
  else {
    *(undefined8 *)p_Var2 = 0;
    *(undefined8 *)(p_Var2 + 8) = 0;
    p_Var3 = *(_Ref_count_base **)(param_1 + 8);
    pIVar4 = *(ImageFrame **)param_1;
    if (p_Var3 != (_Ref_count_base *)0x0) {
      LOCK();
      *(int *)(p_Var3 + 8) = *(int *)(p_Var3 + 8) + 1;
      UNLOCK();
    }
    _Ptr_base<types::ImageFrame>::_Reset0(p_Var2,pIVar4,p_Var3);
    *(longlong *)(this + 8) = *(longlong *)(this + 8) + 0x10;
  }
  return;
}


/* ==================== Meta2FrameIdToUint64 @ 1800846c5  (6 bytes) ==================== */

__uint64 __cdecl device::Meta2FrameIdToUint64(void)

{
  __uint64 _Var1;
  
                    /* WARNING: Could not recover jumptable at 0x0001800846c5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _Var1 = Meta2FrameIdToUint64();
  return _Var1;
}


/* ==================== RoyaleTimestampToSeconds @ 1800846d1  (6 bytes) ==================== */

double __cdecl device::RoyaleTimestampToSeconds(void)

{
  double dVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001800846d1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  dVar1 = RoyaleTimestampToSeconds();
  return dVar1;
}


/* ==================== ConfigureTofCamera @ 18008474f  (6 bytes) ==================== */

ConfigStatus __thiscall
sdc::DriverManagerAdapter::ConfigureTofCamera(DriverManagerAdapter *this,TofConfig *param_1)

{
  ConfigStatus CVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00018008474f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CVar1 = ConfigureTofCamera(this,param_1);
  return CVar1;
}


/* ==================== WriteToFlashMemory @ 180084779  (6 bytes) ==================== */

FlashIoStatus __thiscall
sdc::DriverManagerAdapter::WriteToFlashMemory(DriverManagerAdapter *this,FlashMemoryData *param_1)

{
  FlashIoStatus FVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000180084779. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  FVar1 = WriteToFlashMemory(this,param_1);
  return FVar1;
}


/* ==================== Data_RegisterNewFarDepthFrame @ 18008479d  (6 bytes) ==================== */

EventHandlerStatus __thiscall
sdc::DriverManagerAdapter::Data_RegisterNewFarDepthFrame
          (DriverManagerAdapter *this,
          shared_ptr<sdc::SAQWorkPoolClsT<std::shared_ptr<sdc::ImageData>_>_> *param_1)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00018008479d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewFarDepthFrame(this,param_1);
  return EVar1;
}


/* ==================== Data_RegisterNewMonoFrame @ 1800847a3  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::DriverManagerAdapter::Data_RegisterNewMonoFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001800847a3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewMonoFrame();
  return EVar1;
}


/* ==================== Data_RegisterNewRgbFrame @ 1800847a9  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::DriverManagerAdapter::Data_RegisterNewRgbFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001800847a9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewRgbFrame();
  return EVar1;
}


/* ==================== Data_RegisterNewNearDepthFrame @ 1800847af  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::DriverManagerAdapter::Data_RegisterNewNearDepthFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001800847af. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewNearDepthFrame();
  return EVar1;
}


/* ==================== Data_RegisterNewRawImuFrame @ 1800847b5  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::DriverManagerAdapter::Data_RegisterNewRawImuFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001800847b5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewRawImuFrame();
  return EVar1;
}


/* ==================== Data_RegisterNewFusedImuFrame @ 1800847bb  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::DriverManagerAdapter::Data_RegisterNewFusedImuFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001800847bb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewFusedImuFrame();
  return EVar1;
}


/* ==================== WriteToFlashMemory @ 180084851  (6 bytes) ==================== */

FlashIoStatus __thiscall
sdc::SAQDriverManagerAdapterCls::WriteToFlashMemory
          (SAQDriverManagerAdapterCls *this,FlashMemoryData *param_1)

{
  FlashIoStatus FVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000180084851. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  FVar1 = WriteToFlashMemory(this,param_1);
  return FVar1;
}


/* ==================== Data_RegisterNewFarDepthFrame @ 180084875  (6 bytes) ==================== */

EventHandlerStatus __thiscall
sdc::SAQDriverManagerAdapterCls::Data_RegisterNewFarDepthFrame
          (SAQDriverManagerAdapterCls *this,
          shared_ptr<sdc::SAQWorkPoolClsT<std::shared_ptr<sdc::ImageData>_>_> *param_1)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000180084875. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewFarDepthFrame(this,param_1);
  return EVar1;
}


/* ==================== Data_RegisterNewMonoFrame @ 18008487b  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::SAQDriverManagerAdapterCls::Data_RegisterNewMonoFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00018008487b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewMonoFrame();
  return EVar1;
}


/* ==================== Data_RegisterNewRgbFrame @ 180084881  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::SAQDriverManagerAdapterCls::Data_RegisterNewRgbFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000180084881. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewRgbFrame();
  return EVar1;
}


/* ==================== Data_RegisterNewAltFrame @ 180084887  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::SAQDriverManagerAdapterCls::Data_RegisterNewAltFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000180084887. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewAltFrame();
  return EVar1;
}


/* ==================== Data_RegisterNewNearDepthFrame @ 18008488d  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::SAQDriverManagerAdapterCls::Data_RegisterNewNearDepthFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00018008488d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewNearDepthFrame();
  return EVar1;
}


/* ==================== Data_RegisterNewRawImuFrame @ 180084893  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::SAQDriverManagerAdapterCls::Data_RegisterNewRawImuFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000180084893. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewRawImuFrame();
  return EVar1;
}


/* ==================== Data_RegisterNewFusedImuFrame @ 180084899  (6 bytes) ==================== */

EventHandlerStatus __thiscall sdc::SAQDriverManagerAdapterCls::Data_RegisterNewFusedImuFrame(void)

{
  EventHandlerStatus EVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000180084899. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EVar1 = Data_RegisterNewFusedImuFrame();
  return EVar1;
}


/* ==================== ConfigureTofCamera @ 1800848d5  (6 bytes) ==================== */

ConfigStatus __thiscall
sdc::SAQDriverManagerAdapterCls::ConfigureTofCamera
          (SAQDriverManagerAdapterCls *this,TofConfig *param_1)

{
  ConfigStatus CVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001800848d5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CVar1 = ConfigureTofCamera(this,param_1);
  return CVar1;
}


/* ==================== __CxxFrameHandler3 @ 180087130  (6 bytes) ==================== */

void __CxxFrameHandler3(void)

{
                    /* WARNING: Could not recover jumptable at 0x000180087130. Too many branches */
                    /* WARNING: Subroutine does not return */
                    /* WARNING: Treating indirect jump as call */
  __CxxFrameHandler3();
  return;
}


