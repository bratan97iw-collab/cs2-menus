#pragma once
// Pisex Game Utils / CS2 HUD migration — API declaration only.
// NOT a complete, loadable HUD implementation. Do not deploy to game servers.
// The actual CS2 layout-state storage, engine setter calls and network-change
// notifications must be implemented and verified against the running game.

#include "CBaseEntity.h"
#include "CCSPlayerController.h"
#include "schemasystem.h"
#include <utlvector.h>
#include <utlstring.h>
#include <utlsymbollarge.h>
#include <cstdint>

// The engine's networked record layout must be verified before use.
// Do not instantiate/write these records from C++ without verifying their
// runtime ABI and vector element stride.
struct PisexHudPanelClassRecord;
struct PisexHudDialogVariableRecord;
struct PisexHudLayoutState;

class CCSCustomHudLayout : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CCSCustomHudLayout);

    // These field names are published in the modern CS2 schema.
    SCHEMA_FIELD(CUtlSymbolLarge, m_strLayout);
    SCHEMA_FIELD(bool, m_bObservable);

    // Intentionally no SCHEMA_FIELD for m_vecPlayerLayoutStates and
    // m_globalLayoutState: their embedded/networked storage must be handled
    // through a verified schema collection manipulator, NOT plain CUtlVector.

    // Legacy Pisex entry points used in api_layout.cpp.
    // All definitions intentionally pending a verified implementation.
    void SetHasClass(int playerSlot, CUtlString panelId, CUtlString className, bool hasClass);
    void SetDialogVariableString(int playerSlot, CUtlString panelId, CUtlString variableName, CUtlString value);
    const char* GetDialogVariableString(int playerSlot, CUtlString panelId, CUtlString variableName);
    void SetInputCaptureEnabled(int playerSlot, bool capture);
    bool GetInputCaptureEnabled(int playerSlot);

    void SetGlobalHasClass(const char* panelId, const char* className, bool hasClass);
    void SetGlobalDialogVariableString(const char* panelId, const char* variableName, const char* value);
    void SetGlobalInputCaptureEnabled(bool capture);
};
