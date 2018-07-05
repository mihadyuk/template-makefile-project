/*
 * memalloc.h
 *
 *  Created on: Jul 5, 2018
 *      Author: Andrey
 */

#ifndef MEMALLOC_H_
#define MEMALLOC_H_

#if !defined (DEFAULT_MEMALLOC_LOG_ENABLED)
#define DEFAULT_MEMALLOC_LOG_ENABLED true
#endif

bool memalloc_isLogEnabled();
void memalloc_logEnable(bool enabled);


#endif /* MEMALLOC_H_ */
