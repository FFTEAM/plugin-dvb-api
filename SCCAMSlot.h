/*
 *  vdr-plugin-dvbapi - softcam dvbapi plugin for VDR
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef ___SCCAMSLOT_H
#define ___SCCAMSLOT_H

#include <vdr/dvbdevice.h>
#include "SCCIAdapter.h"
#include "Frame.h"
#include "Filter.h"

#define SLOT_CAID_CHECK   10000

class cDvbapiFilter;
class SCCIAdapter;

class SCCAMSlot : public cCamSlot
{
private:
  SCCIAdapter *sCCIAdapter;
  int slot, cardIndex, version;
  cTimeMs checkTimer;
  bool reset, doReply;
  cTimeMs resetTimer;
  eModuleStatus lastStatus;
  cRingBufferLinear rb;
  Frame frame;

public:
  SCCAMSlot(SCCIAdapter *ca, int cardIndex, int slot);
  int GetLength(const unsigned char *&data);
  int LengthSize(int n);
  void SetSize(int n, unsigned char *&p);
  void CaInfo(int tcid, int cid);
  bool Check(void);
  void Process(const unsigned char *data, int len);
  eModuleStatus Status(void);
  bool ResetSlot(bool log = true);
  Frame *getFrame(void)
  {
    return &frame;
  }
  uchar *Decrypt(uchar *Data, int &Count);
  virtual const char *GetCamName(void);
  bool ProvidesCa(const int *CaSystemIds);
};

#endif // ___SCCAMSLOT_H
