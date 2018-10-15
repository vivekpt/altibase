/***********************************************************************
 * Copyright 1999-2000, RTBase Corporation or its subsidiaries.
 * All rights reserved.
 **********************************************************************/

/***********************************************************************
 * $Id: iduMutexEntry.h 81183 2017-09-25 08:31:43Z yoonhee.kim $
 **********************************************************************/
#ifndef _O_IDU_MUTEX_ENTRY_H_
#define _O_IDU_MUTEX_ENTRY_H_ 1

#include <idl.h>
#include <iduMutexObj.h>
#include <idvType.h>
#include <iduMutexRes.h>

#define IDU_MUTEX_NAME_LEN (64)

class iduMutexEntry
{
public:
    // for Performance View
    SChar            mName[IDU_MUTEX_NAME_LEN];
    iduMutexRes      mMutex;
    iduMutexOP      *mOP;
    iduMutexKind     mKind;
    idvWeArgs        mWeArgs;
    idvWeArgs       *mWeArgsPtr;

    iduMutexStat     mStat;
    
    iduMutexEntry   *mAllocNext;
    iduMutexEntry   *mInfoNext;
    iduMutexEntry   *mInfoPrev;

    idBool           mIdle;

public:

    IDE_RC create(iduMutexKind);

    IDE_RC initialize(const SChar*, idvWaitIndex, UInt);

    inline IDE_RC finalize(void)
    {
        IDE_ASSERT(mStat.mAccLockCount == 0);
        mStat.mOwner = (ULong)PDL_INVALID_HANDLE;
        return mOP->mFinalize(&mMutex);
    }

    inline IDE_RC destroy()
    {
        IDE_ASSERT(mStat.mAccLockCount == 0);
        return mOP->mDestroy(&mMutex);
    }

    inline void lock( idvSQL * aStatSQL )
    {
        mOP->mLock( &mMutex,  &mStat, (void*)aStatSQL, (void*)mWeArgsPtr);
        mStat.mAccLockCount++;
        mStat.mOwner = (ULong)idlOS::thr_self();
    }

    inline void trylock( idBool        * aRet )
    {
        mOP->mTryLock(&mMutex, aRet, &mStat);

        if(*aRet == ID_TRUE)
        {
            mStat.mAccLockCount++;
            mStat.mOwner = (ULong)idlOS::thr_self();
        }
        else
        {
            /* Not locked */
        }
    }
    
    inline void unlock()
    {
        mStat.mAccLockCount--;
        mOP->mUnlock(&mMutex,&mStat);
        mStat.mOwner = (ULong)PDL_INVALID_HANDLE;
    }

    inline void* getMutexForCondWait()
    {
        IDE_ASSERT(mKind == IDU_MUTEX_KIND_POSIX);
        return &(mMutex.mPosix.mMutex);
    }
    
    inline idBool setIdle(idBool aIdle) {return (mIdle = aIdle);}
    inline idBool getIdle() {return mIdle;}

    iduMutexEntry*  getNext() { return mAllocNext; }
    void            setNext(iduMutexEntry *aStmt) {  mAllocNext = aStmt; }

    iduMutexEntry*  getNextInfo() { return mInfoNext; }
    void            setNextInfo(iduMutexEntry *aStmt) {  mInfoNext = aStmt; }

    iduMutexEntry*  getPrevInfo() { return mInfoPrev; }
    void            setPrevInfo( iduMutexEntry *aStmt ) { mInfoPrev = aStmt; }

    /* PROJ-2109 : Remove the bottleneck of alloc/free stmts. */
    /* Reset statistic info and change name of a Mutex */
    void             resetStat();
    void             setName(SChar *aName);

    /* BUG-43940 V$mutex에서 mutex lock을 획득한 스레드 ID출력 */
    void             setThreadID();
};


#endif	// _O_MUTEX_ENTRY_H_
