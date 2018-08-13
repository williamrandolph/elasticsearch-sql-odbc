/*
 * Copyright Elasticsearch B.V. and/or licensed to Elasticsearch B.V. under one
 * or more contributor license agreements. Licensed under the Elastic License;
 * you may not use this file except in compliance with the Elastic License.
 */
#ifndef __QUERIES_H__
#define __QUERIES_H__

#include "error.h"
#include "handles.h"

void queries_init();
void clear_resultset(esodbc_stmt_st *stmt);
SQLRETURN TEST_API attach_answer(esodbc_stmt_st *stmt, char *buff,
	size_t blen);
SQLRETURN TEST_API attach_error(esodbc_stmt_st *stmt, char *buff, size_t blen);
SQLRETURN TEST_API attach_sql(esodbc_stmt_st *stmt, const SQLWCHAR *sql,
	size_t tlen);
void detach_sql(esodbc_stmt_st *stmt);
SQLRETURN TEST_API serialize_statement(esodbc_stmt_st *stmt, cstr_st *buff);


SQLRETURN EsSQLBindCol(
	SQLHSTMT StatementHandle,
	SQLUSMALLINT ColumnNumber,
	SQLSMALLINT TargetType,
	_Inout_updates_opt_(_Inexpressible_(BufferLength))
	SQLPOINTER TargetValue,
	SQLLEN BufferLength,
	_Inout_opt_ SQLLEN *StrLen_or_Ind);
SQLRETURN EsSQLFetch(SQLHSTMT StatementHandle);
SQLRETURN EsSQLGetData(
	SQLHSTMT StatementHandle,
	SQLUSMALLINT ColumnNumber,
	SQLSMALLINT TargetType,
	_Out_writes_opt_(_Inexpressible_(BufferLength)) SQLPOINTER TargetValue,
	SQLLEN BufferLength,
	_Out_opt_ SQLLEN *StrLen_or_IndPtr);
SQLRETURN EsSQLSetPos(
	SQLHSTMT        StatementHandle,
	SQLSETPOSIROW   RowNumber,
	SQLUSMALLINT    Operation,
	SQLUSMALLINT    LockType);
SQLRETURN EsSQLBulkOperations(
	SQLHSTMT            StatementHandle,
	SQLSMALLINT         Operation);
SQLRETURN EsSQLMoreResults(SQLHSTMT hstmt);
SQLRETURN EsSQLCloseCursor(SQLHSTMT StatementHandle);
SQLRETURN EsSQLNumResultCols(SQLHSTMT StatementHandle,
	_Out_ SQLSMALLINT *ColumnCount);

SQLRETURN EsSQLPrepareW(
	SQLHSTMT    hstmt,
	_In_reads_(cchSqlStr) SQLWCHAR *szSqlStr,
	SQLINTEGER  cchSqlStr);
SQLRETURN EsSQLBindParameter(
	SQLHSTMT        StatementHandle,
	SQLUSMALLINT    ParameterNumber,
	SQLSMALLINT     InputOutputType,
	SQLSMALLINT     ValueType,
	SQLSMALLINT     ParameterType,
	SQLULEN         ColumnSize,
	SQLSMALLINT     DecimalDigits,
	SQLPOINTER      ParameterValuePtr,
	SQLLEN          BufferLength,
	SQLLEN         *StrLen_or_IndPtr);
SQLRETURN EsSQLExecute(SQLHSTMT hstmt);
SQLRETURN EsSQLExecDirectW(
	SQLHSTMT    hstmt,
	_In_reads_opt_(TextLength) SQLWCHAR *szSqlStr,
	SQLINTEGER cchSqlStr);

SQLRETURN EsSQLDescribeColW(
	SQLHSTMT            hstmt,
	SQLUSMALLINT        icol,
	_Out_writes_opt_(cchColNameMax)
	SQLWCHAR            *szColName,
	SQLSMALLINT         cchColNameMax,
	_Out_opt_
	SQLSMALLINT        *pcchColName,
	_Out_opt_
	SQLSMALLINT        *pfSqlType,
	_Out_opt_
	SQLULEN            *pcbColDef,
	_Out_opt_
	SQLSMALLINT        *pibScale,
	_Out_opt_
	SQLSMALLINT        *pfNullable);
SQLRETURN EsSQLColAttributeW(
	SQLHSTMT        hstmt,
	SQLUSMALLINT    iCol,
	SQLUSMALLINT    iField,
	_Out_writes_bytes_opt_(cbDescMax)
	SQLPOINTER      pCharAttr,
	SQLSMALLINT     cbDescMax,
	_Out_opt_
	SQLSMALLINT     *pcbCharAttr,
	_Out_opt_
#ifdef _WIN64
	SQLLEN          *pNumAttr
#else /* _WIN64 */
	SQLPOINTER      pNumAttr
#endif /* _WIN64 */
);
SQLRETURN EsSQLNumParams(
	SQLHSTMT           StatementHandle,
	_Out_opt_
	SQLSMALLINT       *ParameterCountPtr);
SQLRETURN EsSQLRowCount(_In_ SQLHSTMT StatementHandle, _Out_ SQLLEN *RowCount);


#endif /* __QUERIES_H__ */
