// VS_UI_ui_result_receiver.cpp

#include "client_PCH.h"
#include <assert.h>
#include "VS_UI_ui_result_receiver.h"

/*-----------------------------------------------------------------------------
- C_VS_UI_RESULT_RECEIVER
-
-----------------------------------------------------------------------------*/
C_VS_UI_RESULT_RECEIVER::C_VS_UI_RESULT_RECEIVER()
{
	m_fp_result_receiver = NULL;
}

/*-----------------------------------------------------------------------------
- ~C_VS_UI_RESULT_RECEIVER
-
-----------------------------------------------------------------------------*/
C_VS_UI_RESULT_RECEIVER::~C_VS_UI_RESULT_RECEIVER()
{

}

/*-----------------------------------------------------------------------------
- SetResultReceiver
-
-----------------------------------------------------------------------------*/
void C_VS_UI_RESULT_RECEIVER::SetResultReceiver(void (*fp)(DWORD, int, int, void *))
{
	assert(fp);
	
	m_fp_result_receiver = fp;
}

/*-----------------------------------------------------------------------------
- SendMessage
- Message queue�� message�� �ִ´�.
-----------------------------------------------------------------------------*/
void C_VS_UI_RESULT_RECEIVER::_SendMessage(DWORD message, int left, int right, 
															 void *void_ptr)
{
	assert(message != INVALID_MESSAGE);

	MESSAGE * msg = new MESSAGE;

	msg->message = message;
	msg->left = left;
	msg->right = right;
	msg->void_ptr = void_ptr;

	m_message_queue.Add(msg);
}

/*-----------------------------------------------------------------------------
- DispatchMessage
- ���� ���� ����� message�� �� �� ������. �׸��� �װ��� queue���� �����Ѵ�.
-----------------------------------------------------------------------------*/
void C_VS_UI_RESULT_RECEIVER::_DispatchMessage()
{
	if (m_fp_result_receiver != NULL)
	{
		if (m_message_queue.Size() > 0)
		{
			MESSAGE * data;
			if (m_message_queue.Data(0, data))
			{
				// Remove from queue BEFORE calling the handler and freeing.
				// The handler can re-enter _DispatchMessage (Windows CriticalSections
				// are recursive), which would dispatch the same MESSAGE again
				// and double-free it.
				m_message_queue.Delete(data);

				// Copy fields before freeing, in case data is on a guard page
				DWORD msg   = data->message;
				int   left  = data->left;
				int   right = data->right;
				void* vptr  = data->void_ptr;
				delete data;

				m_fp_result_receiver(msg, left, right, vptr);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// C_MESSAGE_QUEUE
//
// 
//-----------------------------------------------------------------------------
C_MESSAGE_QUEUE::C_MESSAGE_QUEUE()
{

}

//-----------------------------------------------------------------------------
// ~C_MESSAGE_QUEUE
//
// 
//-----------------------------------------------------------------------------
C_MESSAGE_QUEUE::~C_MESSAGE_QUEUE()
{
	MESSAGE * data;
	for (int i=0; i < Size(); i++)
		if (Data(i, data))
			delete data;
}