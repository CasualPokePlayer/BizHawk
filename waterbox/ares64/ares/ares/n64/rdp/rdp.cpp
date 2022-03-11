#include <n64/n64.hpp>

#if defined(ANGRYLION_RDP)
#include "Gfx #1.3.h"
#endif

namespace ares::Nintendo64 {

RDP rdp;
#include "render.cpp"
#include "io.cpp"
#include "debugger.cpp"
#include "serialization.cpp"

auto RDP::load(Node::Object parent) -> void {
  node = parent->append<Node::Object>("RDP");
  debugger.load(node);

  #if defined(ANGRYLION_RDP)
  angrylion::GFX_INFO gfx;

  gfx.RDRAM = rdram.ram.data;
  gfx.DMEM = rsp.dmem.data;
  gfx.IMEM = rsp.imem.data;

  gfx.DPC_START_REG = []() { return ares::Nintendo64::rdp.readWord(0); };
  gfx.DPC_END_REG = []() { return ares::Nintendo64::rdp.readWord(1); };
  gfx.DPC_CURRENT_REG = []() { return ares::Nintendo64::rdp.readWord(2); };
  gfx.DPC_STATUS_REG = []() { return ares::Nintendo64::rdp.readWord(3); };
  // rest are unused

  // special setters because of course
  gfx.DPC_START_REG_SET = [](u32 val) { ares::Nintendo64::rdp.writeWord(0, val); };
  // 1 doesn't need to be set
  gfx.DPC_CURRENT_REG_SET = [](u32 val) { ares::Nintendo64::rdp.command.current = val; }; // HACK
  gfx.DPC_STATUS_REG_SET = [](u32 val) { ares::Nintendo64::rdp.writeWord(3, val); };

  gfx.VI_STATUS_REG = []() { return ares::Nintendo64::vi.readWord(0); };
  gfx.VI_ORIGIN_REG = []() { return ares::Nintendo64::vi.readWord(1); };
  gfx.VI_WIDTH_REG = []() { return ares::Nintendo64::vi.readWord(2); };
  gfx.VI_INTR_REG = []() { return ares::Nintendo64::vi.readWord(3); };
  gfx.VI_V_CURRENT_LINE_REG = []() { return ares::Nintendo64::vi.readWord(4); };
  gfx.VI_TIMING_REG = []() { return ares::Nintendo64::vi.readWord(5); };
  gfx.VI_V_SYNC_REG = []() { return ares::Nintendo64::vi.readWord(6); };
  gfx.VI_H_SYNC_REG = []() { return ares::Nintendo64::vi.readWord(7); };
  // 8 is unused
  gfx.VI_H_START_REG = []() { return ares::Nintendo64::vi.readWord(9); };
  gfx.VI_V_START_REG = []() { return ares::Nintendo64::vi.readWord(10); };
  // 11 is unused
  gfx.VI_X_SCALE_REG = []() { return ares::Nintendo64::vi.readWord(12); };
  gfx.VI_Y_SCALE_REG = []() { return ares::Nintendo64::vi.readWord(13); };
  gfx.CheckInterrupts = []() { ares::Nintendo64::rdp.syncFull(); };
  angrylion::InitiateGFX(gfx);
  puts("starting RDP video");
  angrylion::RomOpen();
  #endif
}

auto RDP::unload() -> void {
  debugger = {};
  node.reset();

  #if defined(ANGRYLION_RDP)
  angrylion::RomClosed();
  #endif
}

auto RDP::main() -> void {
  step(system.frequency());
}

auto RDP::step(u32 clocks) -> void {
  Thread::clock += clocks;
}

auto RDP::power(bool reset) -> void {
  Thread::reset();
  command = {};
  edge = {};
  shade = {};
  texture = {};
  zbuffer = {};
  rectangle = {};
  other = {};
  fog = {};
  blend = {};
  primitive = {};
  environment = {};
  combine = {};
  tlut = {};
  load_ = {};
  tileSize = {};
  tile = {};
  set = {};
  primitiveDepth = {};
  scissor = {};
  convert = {};
  key = {};
  fillRectangle_ = {};
  io.bist = {};
  io.test = {};
}

}
