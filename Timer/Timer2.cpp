/*-----------------------------------------------------------------------------

	Timer2.cpp

	Timer version 2

-----------------------------------------------------------------------------*/

#include <windows.h>
#include "Timer2.h"

//----------------------------------------------------------------------------
// Global instance
//----------------------------------------------------------------------------
C_TIMER2 gC_timer2;

//----------------------------------------------------------------------------
// C_TIMER2::C_TIMER2
//----------------------------------------------------------------------------
C_TIMER2::C_TIMER2()
{
	m_timer_queue.size = 0;
	m_timer_queue.pS_timerunit = NULL;
	m_id_generator = 0;
}

//----------------------------------------------------------------------------
// C_TIMER2::~C_TIMER2
//----------------------------------------------------------------------------
C_TIMER2::~C_TIMER2()
{
	if (m_timer_queue.pS_timerunit != NULL)
	{
		delete[] m_timer_queue.pS_timerunit;
		m_timer_queue.pS_timerunit = NULL;
	}
	m_timer_queue.size = 0;
}

//----------------------------------------------------------------------------
// C_TIMER2::Add
// Adds a new timer with the given interval (milliseconds) and callback.
// Returns the timer id, or INVALID_TID on failure.
//----------------------------------------------------------------------------
timer_id_t C_TIMER2::Add(ULONGLONG dw_millisec, void (*fp_proc)(void))
{
	// Find a free (fp_proc == NULL) slot or expand
	for (int i = 0; i < m_timer_queue.size; i++)
	{
		if (m_timer_queue.pS_timerunit[i].fp_proc == NULL)
		{
			m_timer_queue.pS_timerunit[i].bl_pause          = 0;
			m_timer_queue.pS_timerunit[i].dw_prev_tickcount = GetTickCount64();
			m_timer_queue.pS_timerunit[i].dw_millisec       = dw_millisec;
			m_timer_queue.pS_timerunit[i].tid               = ++m_id_generator;
			m_timer_queue.pS_timerunit[i].fp_proc           = fp_proc;
			return m_timer_queue.pS_timerunit[i].tid;
		}
	}

	// No free slot — expand the queue by 1
	int new_size = m_timer_queue.size + 1;
	S_TIMERUNIT* new_units = new S_TIMERUNIT[new_size];
	if (new_units == NULL)
		return INVALID_TID;

	for (int i = 0; i < m_timer_queue.size; i++)
		new_units[i] = m_timer_queue.pS_timerunit[i];

	new_units[m_timer_queue.size].bl_pause          = 0;
	new_units[m_timer_queue.size].dw_prev_tickcount = GetTickCount64();
	new_units[m_timer_queue.size].dw_millisec        = dw_millisec;
	new_units[m_timer_queue.size].tid                = ++m_id_generator;
	new_units[m_timer_queue.size].fp_proc            = fp_proc;

	timer_id_t new_tid = new_units[m_timer_queue.size].tid;

	delete[] m_timer_queue.pS_timerunit;
	m_timer_queue.pS_timerunit = new_units;
	m_timer_queue.size = new_size;

	return new_tid;
}

//----------------------------------------------------------------------------
// C_TIMER2::Delete
// Removes the timer with the given tid. Returns true on success.
//----------------------------------------------------------------------------
bool C_TIMER2::Delete(timer_id_t& tid)
{
	for (int i = 0; i < m_timer_queue.size; i++)
	{
		if (m_timer_queue.pS_timerunit[i].tid == tid)
		{
			m_timer_queue.pS_timerunit[i].fp_proc = NULL;
			m_timer_queue.pS_timerunit[i].tid     = INVALID_TID;
			tid = INVALID_TID;
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------------
// C_TIMER2::Pause
//----------------------------------------------------------------------------
void C_TIMER2::Pause(timer_id_t tid)
{
	for (int i = 0; i < m_timer_queue.size; i++)
	{
		if (m_timer_queue.pS_timerunit[i].tid == tid)
		{
			m_timer_queue.pS_timerunit[i].bl_pause = 1;
			return;
		}
	}
}

//----------------------------------------------------------------------------
// C_TIMER2::Continue
//----------------------------------------------------------------------------
void C_TIMER2::Continue(timer_id_t tid)
{
	for (int i = 0; i < m_timer_queue.size; i++)
	{
		if (m_timer_queue.pS_timerunit[i].tid == tid)
		{
			m_timer_queue.pS_timerunit[i].bl_pause          = 0;
			m_timer_queue.pS_timerunit[i].dw_prev_tickcount = GetTickCount64();
			return;
		}
	}
}

//----------------------------------------------------------------------------
// C_TIMER2::Refresh
//----------------------------------------------------------------------------
void C_TIMER2::Refresh(timer_id_t tid)
{
	for (int i = 0; i < m_timer_queue.size; i++)
	{
		if (m_timer_queue.pS_timerunit[i].tid == tid)
		{
			m_timer_queue.pS_timerunit[i].dw_prev_tickcount = GetTickCount64();
			return;
		}
	}
}

//----------------------------------------------------------------------------
// C_TIMER2::ResetSpeed
//----------------------------------------------------------------------------
void C_TIMER2::ResetSpeed(timer_id_t tid, ULONGLONG millisec)
{
	for (int i = 0; i < m_timer_queue.size; i++)
	{
		if (m_timer_queue.pS_timerunit[i].tid == tid)
		{
			m_timer_queue.pS_timerunit[i].dw_millisec       = millisec;
			m_timer_queue.pS_timerunit[i].dw_prev_tickcount = GetTickCount64();
			return;
		}
	}
}

//----------------------------------------------------------------------------
// C_TIMER2::Execute (private)
//----------------------------------------------------------------------------
void C_TIMER2::Execute(S_TIMERUNIT* pS_timerunit)
{
	if (pS_timerunit == NULL || pS_timerunit->fp_proc == NULL)
		return;

	ULONGLONG now = GetTickCount64();
	if (!pS_timerunit->bl_pause &&
	    (now - pS_timerunit->dw_prev_tickcount) >= pS_timerunit->dw_millisec)
	{
		pS_timerunit->dw_prev_tickcount = now;
		pS_timerunit->fp_proc();
	}
}

//----------------------------------------------------------------------------
// C_TIMER2::Execute (public)
//----------------------------------------------------------------------------
void C_TIMER2::Execute()
{
	for (int i = 0; i < m_timer_queue.size; i++)
	{
		if (m_timer_queue.pS_timerunit[i].fp_proc != NULL)
			Execute(&m_timer_queue.pS_timerunit[i]);
	}
}
