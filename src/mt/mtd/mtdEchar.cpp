/** 
 *  Copyright (c) 1999~2017, Altibase Corp. and/or its affiliates. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License, version 3,
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 

/***********************************************************************
 * $Id: mtcDef.h 34251 2009-07-29 04:07:59Z sungminee $
 **********************************************************************/

#include <mte.h>
#include <mtc.h>
#include <mtd.h>
#include <mtl.h>
#include <mtk.h>
#include <mtdTypes.h>
#include <mtuProperty.h>
#include <mtlCollate.h>

extern mtdModule mtdEchar;

// To Remove Warning
const mtdEcharType mtdEcharNull = { 0, 0, {'\0',} };

static IDE_RC mtdInitialize( UInt aNo );

static IDE_RC mtdEstimate( UInt * aColumnSize,
                           UInt * aArguments,
                           SInt * aPrecision,
                           SInt * aScale );

static IDE_RC mtdValue( mtcTemplate* aTemplate,
                        mtcColumn*   aColumn,
                        void*        aValue,
                        UInt*        aValueOffset,
                        UInt         aValueSize,
                        const void*  aToken,
                        UInt         aTokenLength,
                        IDE_RC*      aResult );

static UInt mtdActualSize( const mtcColumn* aColumn,
                           const void*      aRow );

static IDE_RC mtdGetPrecision( const mtcColumn * aColumn,
                               const void      * aRow,
                               SInt            * aPrecision,
                               SInt            * aScale );

static void mtdSetNull( const mtcColumn* aColumn,
                        void*            aRow );

static UInt mtdHash( UInt             aHash,
                     const mtcColumn* aColumn,
                     const void*      aRow );

static idBool mtdIsNull( const mtcColumn* aColumn,
                         const void*      aRow );

static SInt mtdEcharLogicalAscComp( mtdValueInfo * aValueInfo1,
                                    mtdValueInfo * aValueInfo2 );

static SInt mtdEcharLogicalDescComp( mtdValueInfo * aValueInfo1,
                                     mtdValueInfo * aValueInfo2 );

static SInt mtdEcharFixedMtdFixedMtdKeyAscComp( mtdValueInfo * aValueInfo1,
                                                mtdValueInfo * aValueInfo2 );

static SInt mtdEcharFixedMtdFixedMtdKeyDescComp( mtdValueInfo * aValueInfo1,
                                                 mtdValueInfo * aValueInfo2 );

static SInt mtdEcharMtdMtdKeyAscComp( mtdValueInfo * aValueInfo1,
                                      mtdValueInfo * aValueInfo2 );

static SInt mtdEcharMtdMtdKeyDescComp( mtdValueInfo * aValueInfo1,
                                       mtdValueInfo * aValueInfo2 );

static SInt mtdEcharStoredMtdKeyAscComp( mtdValueInfo * aValueInfo1,
                                         mtdValueInfo * aValueInfo2 );

static SInt mtdEcharStoredMtdKeyDescComp( mtdValueInfo * aValueInfo1,
                                          mtdValueInfo * aValueInfo2 );

static SInt mtdEcharStoredStoredKeyAscComp( mtdValueInfo * aValueInfo1,
                                            mtdValueInfo * aValueInfo2 );

static SInt mtdEcharStoredStoredKeyDescComp( mtdValueInfo * aValueInfo1,
                                             mtdValueInfo * aValueInfo2 );

static IDE_RC mtdCanonize( const mtcColumn * aCanon,
                           void**            aCanonized,
                           mtcEncryptInfo  * aCanonInfo,
                           const mtcColumn * aColumn,
                           void*             aValue,
                           mtcEncryptInfo  * aColumnInfo,
                           mtcTemplate     * aTemplate );
    
static void mtdEndian( void* aValue );

static IDE_RC mtdValidate( mtcColumn * aColumn,
                           void      * aValue,
                           UInt        aValueSize);

static IDE_RC mtdStoredValue2MtdValue( UInt              aColumnSize,
                                       void            * aDestValue,
                                       UInt              aDestValueOffset,
                                       UInt              aLength,
                                       const void      * aValue );

static UInt mtdNullValueSize();

static UInt mtdHeaderSize();

static UInt mtdStoreSize( const smiColumn * aColumn );

static mtcName mtdTypeName[1] = {
    { NULL, 5, (void*)"ECHAR" }
};

static mtcColumn mtdColumn;

mtdModule mtdEchar = {
    mtdTypeName,
    &mtdColumn,
    MTD_ECHAR_ID,
    0,
    { SMI_BUILTIN_B_TREE_INDEXTYPE_ID,
      SMI_BUILTIN_B_TREE2_INDEXTYPE_ID,
      0, 0, 0, 0, 0 },
    MTD_ECHAR_ALIGN,
    MTD_GROUP_TEXT|
    MTD_CANON_NEED_WITH_ALLOCATION|
    MTD_CREATE_ENABLE|
    MTD_COLUMN_TYPE_FIXED|
    MTD_SELECTIVITY_DISABLE|
    MTD_CREATE_PARAM_PRECISION|
    MTD_CASE_SENS_TRUE|
    MTD_SEARCHABLE_SEARCHABLE|       // BUG-17020
    MTD_LITERAL_TRUE|
    MTD_VARIABLE_LENGTH_TYPE_TRUE|   // PROJ-1705
    MTD_DATA_STORE_DIVISIBLE_TRUE|   // PROJ-1705
    MTD_DATA_STORE_MTDVALUE_TRUE|    // PROJ-1705
    MTD_ENCRYPT_TYPE_TRUE|           // PROJ-2002
    MTD_PSM_TYPE_ENABLE, // PROJ-1904
    MTD_ECHAR_STORE_PRECISION_MAXIMUM,
    0,
    0,
    (void*)&mtdEcharNull,
    mtdInitialize,
    mtdEstimate,
    mtdValue,
    mtdActualSize,
    mtdGetPrecision,
    mtdSetNull,
    mtdHash,
    mtdIsNull,
    mtd::isTrueNA,
    {
        mtdEcharLogicalAscComp,    // Logical Comparison
        mtdEcharLogicalDescComp
    },
    {
        // Key Comparison
        {
            // mt value들 간의 compare
            mtdEcharFixedMtdFixedMtdKeyAscComp, // Ascending Key Comparison
            mtdEcharFixedMtdFixedMtdKeyDescComp // Descending Key Comparison
        }
        ,
        {
            // mt value들 간의 compare
            mtdEcharMtdMtdKeyAscComp, // Ascending Key Comparison
            mtdEcharMtdMtdKeyDescComp // Descending Key Comparison
        }
        ,
        {
            // mt value와 stored value간의 compare
            mtdEcharStoredMtdKeyAscComp, // Ascending Key Comparison
            mtdEcharStoredMtdKeyDescComp // Descending Key Comparison
        }
        ,
        {
            // stored value들 간의 compare
            mtdEcharStoredStoredKeyAscComp, // Ascending Key Comparison
            mtdEcharStoredStoredKeyDescComp // Descending Key Comparison
        }
        ,
        {
            /* PROJ-2433 : index Direct key와 fixed mt value들 간의 compare */
            mtdEcharFixedMtdFixedMtdKeyAscComp,
            mtdEcharFixedMtdFixedMtdKeyDescComp
        }
        ,
        {
            /* PROJ-2433 : index Direct key와 mt value들 간의 compare */
            mtdEcharMtdMtdKeyAscComp,
            mtdEcharMtdMtdKeyDescComp
        }
    },
    mtdCanonize,
    mtdEndian,
    mtdValidate,
    mtd::selectivityDefault,
    mtd::encodeNA,
    mtd::decodeDefault,
    mtd::compileFmtDefault,
    mtd::valueFromOracleDefault,
    mtd::makeColumnInfoDefault,

    // BUG-28934
    mtk::mergeAndRangeDefault,
    mtk::mergeOrRangeListDefault,

    {    
        // PROJ-1705
        mtdStoredValue2MtdValue,
        // PROJ-2429
        NULL 
    }, 
    mtdNullValueSize,
    mtdHeaderSize,

    //PROJ-2399
    mtdStoreSize
};


IDE_RC mtdInitialize( UInt aNo )
{
    IDE_TEST( mtd::initializeModule( &mtdEchar, aNo )
              != IDE_SUCCESS );

    // mtdColumn의 초기화
    IDE_TEST( mtc::initializeColumn( & mtdColumn,
                                     & mtdEchar,
                                     0,   // arguments
                                     0,   // precision
                                     0 )  // scale
              != IDE_SUCCESS );
    
    return IDE_SUCCESS;
    
    IDE_EXCEPTION_END;
    
    return IDE_FAILURE;
}

IDE_RC mtdEstimate( UInt * aColumnSize,
                    UInt * aArguments,
                    SInt * aPrecision,
                    SInt * /*aScale*/ )
{
    if( *aArguments == 0 )
    {
        *aArguments = 1;
        *aPrecision = MTD_ECHAR_PRECISION_DEFAULT;
    }
    
    IDE_TEST_RAISE( *aArguments != 1, ERR_INVALID_SCALE );

    IDE_TEST_RAISE( *aPrecision < MTD_ECHAR_PRECISION_MINIMUM ||
                    *aPrecision > MTD_ECHAR_PRECISION_MAXIMUM,
                    ERR_INVALID_LENGTH );

    *aColumnSize = ID_SIZEOF(UShort) + ID_SIZEOF(UShort) + *aPrecision;
    
    return IDE_SUCCESS;
    
    IDE_EXCEPTION( ERR_INVALID_LENGTH );
    IDE_SET(ideSetErrorCode(mtERR_ABORT_INVALID_LENGTH));
    
    IDE_EXCEPTION( ERR_INVALID_SCALE );
    IDE_SET(ideSetErrorCode(mtERR_ABORT_INVALID_SCALE));
    
    IDE_EXCEPTION_END;
    
    return IDE_FAILURE;
}

IDE_RC mtdValue( mtcTemplate* aTemplate,
                 mtcColumn*   aColumn,
                 void*        aValue,
                 UInt*        aValueOffset,
                 UInt         aValueSize,
                 const void*  aToken,
                 UInt         aTokenLength,
                 IDE_RC*      aResult )
{
    mtcECCInfo        sInfo;
    UInt              sValueOffset;
    mtdEcharType    * sValue;
    const UChar     * sToken;
    const UChar     * sTokenFence;
    UChar           * sIterator;
    UChar           * sFence;
    UShort            sValueLength;
    UShort            sLength;
    
    sValueOffset = idlOS::align( *aValueOffset, MTD_ECHAR_ALIGN );

    sValue = (mtdEcharType*)( (UChar*)aValue + sValueOffset );

    *aResult = IDE_SUCCESS;

    // To fix BUG-13444
    // tokenFence와 RowFence는 별개의 검사과정이므로,
    // 먼저 RowFence검사 후 TokenFence검사를 해야 한다.
    sIterator = sValue->mValue;
    sFence    = (UChar*)aValue + aValueSize;
    if( sIterator >= sFence )
    {
        *aResult = IDE_FAILURE;
    }
    else
    {    
        for( sToken      = (const UChar*)aToken,
             sTokenFence = sToken + aTokenLength;
             sToken      < sTokenFence;
             sIterator++, sToken++ )
        {
            if( sIterator >= sFence )
            {
                *aResult = IDE_FAILURE;
                break;
            }
            if( *sToken == '\'' )
            {
                sToken++;
                IDE_TEST_RAISE( sToken >= sTokenFence || *sToken != '\'',
                                ERR_INVALID_LITERAL );
            }
            *sIterator = *sToken;
        }
    }
    
    if( *aResult == IDE_SUCCESS )
    {
        // value에 cipher text length 셋팅
        sValue->mCipherLength = sIterator - sValue->mValue;

        //-----------------------------------------------------
        // PROJ-2002 Column Security
        //
        // [padding 제거하는 이유]
        // char type의 compare는 padding을 무시하고 비교한다.
        // 따라서 echar type의 padding을 제거하여 ecc를 생성하면
        // ecc의 memcmp만으로 echar type의 비교가 가능하다.
        // 
        // 단, NULL과 ' ', '  '의 비교를 위하여
        // NULL에 대해서는 ecc를 생성하지 않으며, ' ', '  '는
        // space padding 하나(' ')로 ecc를 생성한다.
        // 
        // 예제) char'NULL' => echar( encrypt(''),   ecc('')  )
        //       char' '    => echar( encrypt(' '),  ecc(' ') )
        //       char'  '   => echar( encrypt('  '), ecc(' ') )
        //       char'a'    => echar( encrypt('a'),  ecc('a') )
        //       char'a '   => echar( encrypt('a '), ecc('a') )
        //-----------------------------------------------------
        
        // padding 제거
        // sEcharValue에서 space pading을 제외한 길이를 찾는다.
        for( sLength = sValue->mCipherLength; sLength > 1; sLength-- )
        {
            if( sValue->mValue[sLength - 1] != ' ' )
            {
                break;
            }
        }

        if( sValue->mCipherLength > 0 )
        {
            IDE_TEST( aTemplate->getECCInfo( aTemplate,
                                             & sInfo )
                      != IDE_SUCCESS );
            
            // value에 ecc value & ecc length 셋팅
            IDE_TEST( aTemplate->encodeECC( & sInfo,
                                            sValue->mValue,
                                            sLength,
                                            sIterator,
                                            & sValue->mEccLength )
                      != IDE_SUCCESS );
        }
        else
        {
            sValue->mEccLength = 0;            
        }
        
        sValueLength = sValue->mCipherLength + sValue->mEccLength;

        // precision, scale 재 설정 후, estimate로 semantic 검사
        aColumn->flag         = 1;
        aColumn->precision    = sValue->mCipherLength != 0 ? sValue->mCipherLength : 1;
        aColumn->scale        = 0;
        aColumn->encPrecision = sValueLength != 0 ? sValueLength : 1;
        aColumn->policy[0]    = '\0';
        
        IDE_TEST( mtdEstimate( & aColumn->column.size,
                               & aColumn->flag,
                               & aColumn->encPrecision,
                               & aColumn->scale )
                  != IDE_SUCCESS );

        aColumn->column.offset   = sValueOffset;
        *aValueOffset            = sValueOffset
                                   + ID_SIZEOF(UShort) + ID_SIZEOF(UShort)
                                   + sValueLength;
    }
    
    return IDE_SUCCESS;
    
    IDE_EXCEPTION( ERR_INVALID_LITERAL );
    {
        IDE_SET(ideSetErrorCode(mtERR_ABORT_INVALID_LITERAL));
    }    
    
    IDE_EXCEPTION_END;
    
    return IDE_FAILURE;
}

UInt mtdActualSize( const mtcColumn* ,
                    const void*      aRow )
{
    return ID_SIZEOF(UShort) + ID_SIZEOF(UShort) +
           ((mtdEcharType*)aRow)->mCipherLength + ((mtdEcharType*)aRow)->mEccLength;
}

IDE_RC mtdGetPrecision( const mtcColumn * ,
                        const void      * aRow,
                        SInt            * aPrecision,
                        SInt            * aScale )
{
    *aPrecision = ((mtdEcharType*)aRow)->mCipherLength;
    *aScale = 0;

    return IDE_SUCCESS;
}

void mtdSetNull( const mtcColumn* /* aColumn */,
                 void*            aRow )
{
    if( aRow != NULL )
    {
        ((mtdEcharType*)aRow)->mCipherLength = 0;
        ((mtdEcharType*)aRow)->mEccLength = 0;
    }
}

UInt mtdHash( UInt             aHash,
              const mtcColumn* ,
              const void*      aRow )
{
    // ecc로 해시 수행
    return mtc::hash( aHash, 
                ((mtdEcharType*)aRow)->mValue + ((mtdEcharType*)aRow)->mCipherLength,
                ((mtdEcharType*)aRow)->mEccLength );
}

idBool mtdIsNull( const mtcColumn* ,
                  const void*      aRow )
{
    if ( ((mtdEcharType*)aRow)->mEccLength == 0 )
    {
        IDE_ASSERT_MSG( ((mtdEcharType*)aRow)->mCipherLength == 0,
                        "mCipherLength : %"ID_UINT32_FMT"\n",
                        ((mtdEcharType*)aRow)->mCipherLength );
        return ID_TRUE;
    }
    else
    {
        return ID_FALSE;
    }
}

SInt mtdEcharLogicalAscComp( mtdValueInfo * aValueInfo1,
                             mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Mtd 타입의 Key들 간의 ascending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    const mtdEcharType  * sEcharValue1;
    const mtdEcharType  * sEcharValue2;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;

    //---------
    // value1
    //---------
    sEcharValue1 = (const mtdEcharType*)MTD_VALUE_OFFSET_USELESS( aValueInfo1 );
    sEccLength1  = sEcharValue1->mEccLength;

    //---------
    // value2
    //---------
    sEcharValue2 = (const mtdEcharType*)MTD_VALUE_OFFSET_USELESS( aValueInfo2 );
    sEccLength2  = sEcharValue2->mEccLength;

    //---------
    // compare
    //---------

    // ecc로 비교
    if( (sEccLength1 != 0) && (sEccLength2 != 0) )
    {
        sValue1  = sEcharValue1->mValue + sEcharValue1->mCipherLength;
        sValue2  = sEcharValue2->mValue + sEcharValue2->mCipherLength;
    
        if( sEccLength1 > sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength2 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength1 < sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }
}

SInt mtdEcharLogicalDescComp( mtdValueInfo * aValueInfo1,
                              mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Mtd 타입의 Key들 간의 descending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    const mtdEcharType  * sEcharValue1;
    const mtdEcharType  * sEcharValue2;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;    

    //---------
    // value1
    //---------
    sEcharValue1 = (const mtdEcharType*)MTD_VALUE_OFFSET_USELESS( aValueInfo1 );
    sEccLength1  = sEcharValue1->mEccLength;

    //---------
    // value2
    //---------
    sEcharValue2 = (const mtdEcharType*)MTD_VALUE_OFFSET_USELESS( aValueInfo2 );
    sEccLength2  = sEcharValue2->mEccLength;

    //---------
    // compare
    //---------

    // ecc로 비교
    if( (sEccLength1 != 0) && (sEccLength2 != 0) )
    {
        sValue1  = sEcharValue1->mValue + sEcharValue1->mCipherLength;
        sValue2  = sEcharValue2->mValue + sEcharValue2->mCipherLength;
    
        if( sEccLength2 > sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength1 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength2 < sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }
}

SInt mtdEcharFixedMtdFixedMtdKeyAscComp( mtdValueInfo * aValueInfo1,
                                         mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Mtd 타입의 Key들 간의 ascending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    const mtdEcharType  * sEcharValue1;
    const mtdEcharType  * sEcharValue2;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;    

    //---------
    // value1
    //---------
    sEcharValue1 = (const mtdEcharType*)MTD_VALUE_FIXED( aValueInfo1 );
    sEccLength1  = sEcharValue1->mEccLength;

    //---------
    // value2
    //---------
    sEcharValue2 = (const mtdEcharType*)MTD_VALUE_FIXED( aValueInfo2 );
    sEccLength2  = sEcharValue2->mEccLength;

    //---------
    // compare
    //---------

    // ecc로 비교
    if( (sEccLength1 != 0) && (sEccLength2 != 0) )
    {
        sValue1  = sEcharValue1->mValue + sEcharValue1->mCipherLength;
        sValue2  = sEcharValue2->mValue + sEcharValue2->mCipherLength;
    
        if( sEccLength1 > sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength2 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength1 < sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }
}

SInt mtdEcharFixedMtdFixedMtdKeyDescComp( mtdValueInfo * aValueInfo1,
                                          mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Mtd 타입의 Key들 간의 descending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    const mtdEcharType  * sEcharValue1;
    const mtdEcharType  * sEcharValue2;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;    

    //---------
    // value1
    //---------
    sEcharValue1 = (const mtdEcharType*)MTD_VALUE_FIXED( aValueInfo1 );
    sEccLength1  = sEcharValue1->mEccLength;

    //---------
    // value2
    //---------
    sEcharValue2 = (const mtdEcharType*)MTD_VALUE_FIXED( aValueInfo2 );
    sEccLength2  = sEcharValue2->mEccLength;

    //---------
    // compare
    //---------

    // ecc로 비교
    if( (sEccLength1 != 0) && (sEccLength2 != 0) )
    {
        sValue1  = sEcharValue1->mValue + sEcharValue1->mCipherLength;
        sValue2  = sEcharValue2->mValue + sEcharValue2->mCipherLength;
    
        if( sEccLength2 > sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength1 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength2 < sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }
}

SInt mtdEcharMtdMtdKeyAscComp( mtdValueInfo * aValueInfo1,
                               mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Mtd 타입의 Key들 간의 ascending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    const mtdEcharType  * sEcharValue1;
    const mtdEcharType  * sEcharValue2;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;

    //---------
    // value1
    //---------
    sEcharValue1 = (mtdEcharType*)
        mtd::valueForModule( (smiColumn*)aValueInfo1->column,
                             aValueInfo1->value,
                             aValueInfo1->flag,
                             mtdEchar.staticNull );

    sEccLength1  = sEcharValue1->mEccLength;

    //---------
    // value2
    //---------
    sEcharValue2 = (mtdEcharType*)
        mtd::valueForModule( (smiColumn*)aValueInfo2->column,
                             aValueInfo2->value,
                             aValueInfo2->flag,
                             mtdEchar.staticNull );

    sEccLength2  = sEcharValue2->mEccLength;

    //---------
    // compare
    //---------

    // ecc로 비교
    if( (sEccLength1 != 0) && (sEccLength2 != 0) )
    {
        sValue1  = sEcharValue1->mValue + sEcharValue1->mCipherLength;
        sValue2  = sEcharValue2->mValue + sEcharValue2->mCipherLength;
    
        if( sEccLength1 > sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength2 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength1 < sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }
}

SInt mtdEcharMtdMtdKeyDescComp( mtdValueInfo * aValueInfo1,
                                mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Mtd 타입의 Key들 간의 descending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    const mtdEcharType  * sEcharValue1;
    const mtdEcharType  * sEcharValue2;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;    

    //---------
    // value1
    //---------
    sEcharValue1 = (mtdEcharType*)
        mtd::valueForModule( (smiColumn*)aValueInfo1->column,
                             aValueInfo1->value,
                             aValueInfo1->flag,
                             mtdEchar.staticNull );

    sEccLength1  = sEcharValue1->mEccLength;

    //---------
    // value2
    //---------
    sEcharValue2 = (mtdEcharType*)
        mtd::valueForModule( (smiColumn*)aValueInfo2->column,
                             aValueInfo2->value,
                             aValueInfo2->flag,
                             mtdEchar.staticNull );

    sEccLength2  = sEcharValue2->mEccLength;

    //---------
    // compare
    //---------

    // ecc로 비교
    if( (sEccLength1 != 0) && (sEccLength2 != 0) )
    {
        sValue1  = sEcharValue1->mValue + sEcharValue1->mCipherLength;
        sValue2  = sEcharValue2->mValue + sEcharValue2->mCipherLength;
    
        if( sEccLength2 > sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength1 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength2 < sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }
}

SInt mtdEcharStoredMtdKeyAscComp( mtdValueInfo * aValueInfo1,
                                  mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Mtd 타입의 Key와 Stored Key 간의 ascending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    const mtdEcharType  * sEcharValue2;
    UShort                sCipherLength1;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;    

    //---------
    // value1
    //---------
    if ( aValueInfo1->length != 0 )
    {
        ID_SHORT_BYTE_ASSIGN( &sEccLength1,
                              (UChar*)aValueInfo1->value + ID_SIZEOF(UShort) );
    }
    else
    {
        sEccLength1 = 0;
    }
    
    //---------
    // value2
    //---------    
    sEcharValue2 = (const mtdEcharType*)
                   mtd::valueForModule( (smiColumn*)aValueInfo2->column,
                                        aValueInfo2->value,
                                        aValueInfo2->flag,
                                        mtdEchar.staticNull );
    sEccLength2 = sEcharValue2->mEccLength;

    //---------
    // compare
    //---------

    // ecc로 비교
    if( (sEccLength1 != 0) && (sEccLength2 != 0) )
    {
        ID_SHORT_BYTE_ASSIGN( &sCipherLength1,
                              (UChar*)aValueInfo1->value );
        
        sValue1  = (UChar*)aValueInfo1->value + mtdHeaderSize() + sCipherLength1;
        sValue2  = sEcharValue2->mValue + sEcharValue2->mCipherLength;
    
        if( sEccLength1 > sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength2 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength1 < sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }
}

SInt mtdEcharStoredMtdKeyDescComp( mtdValueInfo * aValueInfo1,
                                   mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Mtd 타입의 Key와 Stored Key 간의 descending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    const mtdEcharType  * sEcharValue2;
    UShort                sCipherLength1;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;    

    //---------
    // value1
    //---------
    if ( aValueInfo1->length != 0 )
    {
        ID_SHORT_BYTE_ASSIGN( &sEccLength1,
                              (UChar*)aValueInfo1->value + ID_SIZEOF(UShort) );
    }
    else
    {
        sEccLength1 = 0;
    }
    
    //---------
    // value2
    //---------    
    sEcharValue2 = (const mtdEcharType*)
                   mtd::valueForModule( (smiColumn*)aValueInfo2->column,
                                        aValueInfo2->value,
                                        aValueInfo2->flag,
                                        mtdEchar.staticNull );
    sEccLength2 = sEcharValue2->mEccLength;

    //---------
    // compare
    //---------

    // ecc로 비교
    if( (sEccLength1 != 0) && (sEccLength2 != 0) )
    {
        ID_SHORT_BYTE_ASSIGN( &sCipherLength1,
                              (UChar*)aValueInfo1->value );

        sValue1  = (UChar*)aValueInfo1->value + mtdHeaderSize() + sCipherLength1;
        sValue2  = sEcharValue2->mValue + sEcharValue2->mCipherLength;
    
        if( sEccLength2 > sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength1 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength2 < sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }
}

SInt mtdEcharStoredStoredKeyAscComp( mtdValueInfo * aValueInfo1,
                                     mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Stored Key들 간의 ascending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    UShort                sCipherLength1;
    UShort                sCipherLength2;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;    

    //---------
    // value1
    //---------
    if ( aValueInfo1->length != 0 )
    {
        ID_SHORT_BYTE_ASSIGN( &sEccLength1,
                              (UChar*)aValueInfo1->value + ID_SIZEOF(UShort) );
    }
    else
    {
        sEccLength1 = 0;
    }
    
    //---------
    // value2
    //---------
    if ( aValueInfo2->length != 0 )
    {
        ID_SHORT_BYTE_ASSIGN( &sEccLength2,
                              (UChar*)aValueInfo2->value + ID_SIZEOF(UShort) );
    }
    else
    {
        sEccLength2 = 0;
    }
    
    //---------
    // compare
    //---------

    // ecc로 비교
    if( (sEccLength1 != 0) && (sEccLength2 != 0) )
    {
        ID_SHORT_BYTE_ASSIGN( &sCipherLength1,
                              (UChar*)aValueInfo1->value );
        ID_SHORT_BYTE_ASSIGN( &sCipherLength2,
                              (UChar*)aValueInfo2->value );

        sValue1  = (UChar*)aValueInfo1->value + mtdHeaderSize() + sCipherLength1;
        sValue2  = (UChar*)aValueInfo2->value + mtdHeaderSize() + sCipherLength2;
        
        if( sEccLength1 > sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength2 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength1 < sEccLength2 )
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue1,
                                  sValue2,
                                  sEccLength1 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }
}

SInt mtdEcharStoredStoredKeyDescComp( mtdValueInfo * aValueInfo1,
                                      mtdValueInfo * aValueInfo2 )
{
/***********************************************************************
 *
 * Description : Stored Key들 간의 descending compare
 *
 * Implementation :
 *
 ***********************************************************************/

    UShort                sCipherLength1;
    UShort                sCipherLength2;
    UShort                sEccLength1;
    UShort                sEccLength2;
    const UChar         * sValue1;
    const UChar         * sValue2;    

    //---------
    // value1
    //---------
    if ( aValueInfo1->length != 0 )
    {
        ID_SHORT_BYTE_ASSIGN( &sEccLength1,
                              (UChar*)aValueInfo1->value + ID_SIZEOF(UShort) );
    }
    else
    {
        sEccLength1 = 0;
    }
    
    //---------
    // value2
    //---------
    if ( aValueInfo2->length != 0 )
    {
        ID_SHORT_BYTE_ASSIGN( &sEccLength2,
                              (UChar*)aValueInfo2->value + ID_SIZEOF(UShort) );
    }
    else
    {
        sEccLength2 = 0;
    }
    
    //---------
    // compare
    //---------

    // ecc로 비교
    if( (aValueInfo1->length != 0) && (aValueInfo2->length != 0) )
    {
        ID_SHORT_BYTE_ASSIGN( &sCipherLength1,
                              (UChar*)aValueInfo1->value );
        ID_SHORT_BYTE_ASSIGN( &sCipherLength2,
                              (UChar*)aValueInfo2->value );

        sValue1  = (UChar*)aValueInfo1->value + mtdHeaderSize() + sCipherLength1;
        sValue2  = (UChar*)aValueInfo2->value + mtdHeaderSize() + sCipherLength2;
    
        if( sEccLength2 > sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength1 ) >= 0 ? 1 : -1 ;
        }
        else if( sEccLength2 < sEccLength1 )
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 ) > 0 ? 1 : -1 ;
        }
        else
        {
            return idlOS::memcmp( sValue2,
                                  sValue1,
                                  sEccLength2 );
        }
    }
    else
    {
        if( sEccLength1 < sEccLength2 )
        {
            return 1;
        }
        if( sEccLength1 > sEccLength2 )
        {
            return -1;
        }
        return 0;
    }    
}

static IDE_RC mtdCanonize( const mtcColumn * aCanon,
                           void**            aCanonized,
                           mtcEncryptInfo  * aCanonInfo,
                           const mtcColumn * aColumn,
                           void*             aValue,
                           mtcEncryptInfo  * aColumnInfo,
                           mtcTemplate     * aTemplate )
{
    mtdEcharType  * sCanonized;
    mtdEcharType  * sValue;
    UChar           sDecryptedBuf[MTD_ECHAR_DECRYPT_BUFFER_SIZE];
    UChar         * sPlain;
    UShort          sPlainLength;
        
    sValue = (mtdEcharType*)aValue;
    sCanonized = (mtdEcharType*)*aCanonized;
    sPlain = sDecryptedBuf;
    
    // 컬럼의 보안정책으로 암호화
    if( ( aColumn->policy[0] == '\0' ) && ( aCanon->policy[0] == '\0' ) )
    {
        //-----------------------------------------------------
        // case 1. default policy -> default policy
        //-----------------------------------------------------
        
        if( sValue->mCipherLength == aCanon->precision )
        {
            IDE_TEST_RAISE( sValue->mCipherLength + sValue->mEccLength >
                        aCanon->encPrecision, ERR_INVALID_LENGTH );
            
            *aCanonized = aValue;
        }
        else
        {
            if( sValue->mEccLength == 0 )
            {
                IDE_ASSERT_MSG( sValue->mCipherLength == 0,
                                "sValue->mCipherLength : %"ID_UINT32_FMT"\n",
                                sValue->mCipherLength );
                *aCanonized = aValue;
            }
            else
            {
                IDE_TEST_RAISE( sValue->mCipherLength > aCanon->precision,
                                ERR_INVALID_LENGTH );

                // a. copy cipher value
                if( sValue->mCipherLength > 0 )
                {
                    idlOS::memcpy( sCanonized->mValue,
                                   sValue->mValue,
                                   sValue->mCipherLength );
                }
                else
                {
                    // Nothing to do.
                }
            
                // b. padding
                if( ( aCanon->precision - sValue->mCipherLength ) > 0 )
                {
                    idlOS::memset( sCanonized->mValue + sValue->mCipherLength, ' ',
                                   aCanon->precision - sValue->mCipherLength );
                }
                else
                {
                    // Nothing to do.
                }
            
                // c. copy ecc value
                IDE_TEST_RAISE( ( aCanon->precision + sValue->mEccLength ) >
                                  aCanon->encPrecision, ERR_INVALID_LENGTH );
            
                idlOS::memcpy( sCanonized->mValue + aCanon->precision,
                               sValue->mValue + sValue->mCipherLength,
                               sValue->mEccLength );
            
                sCanonized->mCipherLength = aCanon->precision;
                sCanonized->mEccLength    = sValue->mEccLength;
            }
        }
    }
    else if( ( aColumn->policy[0] != '\0' ) && ( aCanon->policy[0] == '\0' ) )
    {
        //-----------------------------------------------------
        // case 2. policy1 -> default policy
        //-----------------------------------------------------
        
        IDE_ASSERT( aColumnInfo != NULL );

        if( sValue->mEccLength == 0 )
        {
            IDE_ASSERT_MSG( sValue->mCipherLength == 0,
                            "sValue->mCipherLength : %"ID_UINT32_FMT"\n",
                            sValue->mCipherLength );
            *aCanonized = aValue;
        }
        else
        {
            // a. copy cipher value
            if( sValue->mCipherLength > 0 )
            {            
                IDE_TEST( aTemplate->decrypt( aColumnInfo,
                                              (SChar*) aColumn->policy,
                                              sValue->mValue,
                                              sValue->mCipherLength,
                                              sPlain,
                                              & sPlainLength )
                          != IDE_SUCCESS );
                
                IDE_ASSERT_MSG( sPlainLength <= aColumn->precision,
                                "sPlainLength : %"ID_UINT32_FMT"\n"
                                "aColumn->precision : %"ID_UINT32_FMT"\n",
                                sPlainLength, aColumn->precision );

                IDE_TEST_RAISE( sPlainLength > aCanon->precision,
                                ERR_INVALID_LENGTH );

                idlOS::memcpy( sCanonized->mValue,
                               sPlain,
                               sPlainLength );
            }
            else
            {
                sPlainLength = 0;
            }
            
            // b. padding
            if( aCanon->precision - sPlainLength > 0 )
            {
                idlOS::memset( sCanonized->mValue + sPlainLength, ' ',
                               aCanon->precision - sPlainLength );
            }
            else
            {
                // Nothing to do.
            }
            
            // c. copy ecc value
            IDE_TEST_RAISE( ( aCanon->precision + sValue->mEccLength ) >
                              aCanon->encPrecision, ERR_INVALID_LENGTH );
            
            idlOS::memcpy( sCanonized->mValue + aCanon->precision,
                           sValue->mValue + sValue->mCipherLength,
                           sValue->mEccLength );
            
            sCanonized->mCipherLength = aCanon->precision;
            sCanonized->mEccLength    = sValue->mEccLength;
        }
    }
    else if( ( aColumn->policy[0] == '\0' ) && ( aCanon->policy[0] != '\0' ) )
    {
        //-----------------------------------------------------
        // case 3. default policy -> policy2
        // 
        // ex) echar(1,def) {1,'a',ecc('a')}
        //     -> echar(3,p1) {3,enc('a  '),ecc('a')}
        //-----------------------------------------------------
        
        IDE_ASSERT( aCanonInfo != NULL );

        if( sValue->mEccLength == 0 )
        {
            IDE_ASSERT_MSG( sValue->mCipherLength == 0,
                            "sValue->mCipherLength : %"ID_UINT32_FMT"\n",
                            sValue->mCipherLength );
            *aCanonized = aValue;
        }
        else
        {
            IDE_TEST_RAISE( sValue->mCipherLength > aCanon->precision,
                            ERR_INVALID_LENGTH );

            // a. padding
            if( sValue->mCipherLength > 0 )
            {
                idlOS::memcpy( sPlain,
                               sValue->mValue,
                               sValue->mCipherLength );
            }
            else
            {
                // Nothing to do.
            }

            if( aCanon->precision - sValue->mCipherLength > 0 )
            {
                idlOS::memset( sPlain + sValue->mCipherLength,
                               ' ',
                               aCanon->precision - sValue->mCipherLength );
            }
            else
            {
                // Nothing to do.
            }            

            // b. copy cipher value
            IDE_TEST( aTemplate->encrypt( aCanonInfo,
                                          (SChar*) aCanon->policy,
                                          sPlain,
                                          aCanon->precision,
                                          sCanonized->mValue,
                                          & sCanonized->mCipherLength )
                      != IDE_SUCCESS );
        
            // c. copy ecc value
            IDE_TEST_RAISE( ( sCanonized->mCipherLength + sValue->mEccLength ) >
                              aCanon->encPrecision, ERR_INVALID_LENGTH );
            
            idlOS::memcpy( sCanonized->mValue + sCanonized->mCipherLength,
                           sValue->mValue + sValue->mCipherLength,
                           sValue->mEccLength );
        
            sCanonized->mEccLength = sValue->mEccLength;
        }
    }
    else 
    {
        //-----------------------------------------------------
        // case 4. policy1 -> policy2
        //-----------------------------------------------------

        IDE_ASSERT( aColumnInfo != NULL );
        IDE_ASSERT( aCanonInfo != NULL );

        if( sValue->mEccLength == 0 )
        {
            IDE_ASSERT_MSG( sValue->mCipherLength == 0,
                            "sValue->mCipherLength : %"ID_UINT32_FMT"\n",
                            sValue->mCipherLength );
            *aCanonized = aValue;
        }
        else
        {
            // a. decrypt
            if( sValue->mCipherLength > 0 )
            {            
                IDE_TEST( aTemplate->decrypt( aColumnInfo,
                                              (SChar*) aColumn->policy,
                                              sValue->mValue,
                                              sValue->mCipherLength,
                                              sPlain,
                                              & sPlainLength )
                          != IDE_SUCCESS );
                    
                IDE_ASSERT_MSG( sPlainLength <= aColumn->precision,
                                "sPlainLength : %"ID_UINT32_FMT"\n"
                                "aColumn->precision : %"ID_UINT32_FMT"\n",
                                sPlainLength, aColumn->precision );
                    
                IDE_TEST_RAISE( sPlainLength > aCanon->precision,
                                ERR_INVALID_LENGTH );
            }
            else
            {
                sPlainLength = 0;
            }

            // b. padding
            if( aCanon->precision - sPlainLength > 0 )
            {
                idlOS::memset( sPlain + sPlainLength,
                               ' ',
                               aCanon->precision - sPlainLength );
            }
            else
            {
                // Nothing to do.
            }    
                
            // c. copy cipher value
            IDE_TEST( aTemplate->encrypt( aCanonInfo,
                                          (SChar*) aCanon->policy,
                                          sPlain,
                                          aCanon->precision,
                                          sCanonized->mValue,
                                          & sCanonized->mCipherLength )
                      != IDE_SUCCESS );
                
            // d. copy ecc value
            IDE_TEST_RAISE( ( sCanonized->mCipherLength + sValue->mEccLength ) >
                              aCanon->encPrecision, ERR_INVALID_LENGTH );
            
            idlOS::memcpy( sCanonized->mValue + sCanonized->mCipherLength,
                           sValue->mValue + sValue->mCipherLength,
                           sValue->mEccLength );
            
            sCanonized->mEccLength = sValue->mEccLength;
        }
    }
    
    return IDE_SUCCESS;

    IDE_EXCEPTION( ERR_INVALID_LENGTH );
    {
        IDE_SET(ideSetErrorCode(mtERR_ABORT_INVALID_LENGTH));
    }
    IDE_EXCEPTION_END;

    return IDE_FAILURE;
}

void mtdEndian( void* aValue )
{
    UChar* sLength;
    UChar  sIntermediate;
    
    sLength = (UChar*)&(((mtdEcharType*)aValue)->mCipherLength);
    
    sIntermediate = sLength[0];
    sLength[0]    = sLength[1];
    sLength[1]    = sIntermediate;

    sLength = (UChar*)&(((mtdEcharType*)aValue)->mEccLength);
    
    sIntermediate = sLength[0];
    sLength[0]    = sLength[1];
    sLength[1]    = sIntermediate;
}


IDE_RC mtdValidate( mtcColumn * aColumn,
                    void      * aValue,
                    UInt        aValueSize)
{
/***********************************************************************
 *
 * Description : value의 semantic 검사 및 mtcColumn 초기화
 *
 * Implementation :
 *
 ***********************************************************************/
        
    mtdEcharType * sEcharVal = (mtdEcharType*)aValue;
    IDE_TEST_RAISE( sEcharVal == NULL, ERR_INVALID_NULL );
    
    IDE_TEST_RAISE( aValueSize < ID_SIZEOF(UShort), ERR_INVALID_LENGTH);
    IDE_TEST_RAISE( sEcharVal->mCipherLength + sEcharVal->mEccLength
                    + ID_SIZEOF(UShort) + ID_SIZEOF(UShort) != aValueSize,
                    ERR_INVALID_LENGTH );
    
    // 초기화된 aColumn은 cannonize() 시에 사용
    // 이때, data type module의 precision 정보만을 사용하므로,
    // language 정보 설정할 필요없음
    IDE_TEST( mtc::initializeColumn( aColumn,
                                     & mtdEchar,
                                     1,                           // arguments
                                     sEcharVal->mCipherLength,    // precision
                                     0 )
              != IDE_SUCCESS );

    IDE_TEST( mtc::initializeEncryptColumn(
                  aColumn,
                  (const SChar*)"",         // policy
                  sEcharVal->mCipherLength, // encryptedSize
                  sEcharVal->mEccLength )   // ECCSize
              != IDE_SUCCESS );

    return IDE_SUCCESS;

    IDE_EXCEPTION( ERR_INVALID_NULL);
    {
        IDE_SET(ideSetErrorCode(mtERR_ABORT_VALIDATE_INVALID_VALUE));
    }
    IDE_EXCEPTION( ERR_INVALID_LENGTH );
    {
        IDE_SET(ideSetErrorCode(mtERR_ABORT_VALIDATE_INVALID_LENGTH));
    }
    IDE_EXCEPTION_END;

    return IDE_FAILURE;
}

static IDE_RC mtdStoredValue2MtdValue( UInt              aColumnSize,
                                       void            * aDestValue,
                                       UInt              aDestValueOffset,
                                       UInt              aLength,
                                       const void      * aValue )
{
/*******************************************************************
 * PROJ-1705
 * 디스크테이블컬럼의 데이타를
 * qp 레코드처리영역의 해당 컬럼위치에 복사
 *******************************************************************/

    mtdEcharType* sEcharValue;

    sEcharValue = (mtdEcharType*)aDestValue;
    
    if( ( aDestValueOffset == 0 ) && ( aLength == 0 ) )
    {
        // NULL 데이타
        sEcharValue->mCipherLength = 0;
        sEcharValue->mEccLength = 0;
    }
    else
    {
        IDE_TEST_RAISE( (aDestValueOffset + aLength) > aColumnSize, ERR_INVALID_STORED_VALUE );

        idlOS::memcpy( (UChar*)sEcharValue + aDestValueOffset,
                       aValue,
                       aLength );
    }

    return IDE_SUCCESS;

    IDE_EXCEPTION(ERR_INVALID_STORED_VALUE);
    {
        IDE_SET(ideSetErrorCode(mtERR_ABORT_INVALID_STORED_DATA_LENGTH));
    }

    IDE_EXCEPTION_END;

    return IDE_FAILURE;
}

UInt mtdNullValueSize()
{
/*******************************************************************
 * PROJ-1705
 * 각 데이타타입의 null Value의 크기 반환
 * 예 ) mtdEcharType( UShort length; UChar value[1] ) 에서
 *      length 타입인 UShort의 크기를 반환
 *******************************************************************/
    return mtdActualSize( NULL, &mtdEcharNull );
}

static UInt mtdHeaderSize()
{
/***********************************************************************
 * PROJ-1705
 * length를 가지는 데이타타입의 length 정보를 저장하는 변수의 크기 반환
 * 예 ) mtdEcharType( UShort length; UChar value[1] ) 에서
 *      length 타입인 UShort의 크기를 반환
 *  integer와 같은 고정길이 데이타타입은 0 반환
 **********************************************************************/

    return ID_SIZEOF(UShort) + ID_SIZEOF(UShort);
}

static UInt mtdStoreSize( const smiColumn * /*aColumn*/ ) 
{
/***********************************************************************
 * PROJ-2399 row tmaplate 
 * sm에 저장되는 데이터의 크기를 반환한다.
 * variable 타입의 데이터 타입은 ID_UINT_MAX를 반환
 * mtheader가 sm에 저장된경우가 아니면 mtheader크기를 빼서 반환
 **********************************************************************/

    return ID_UINT_MAX;
}
