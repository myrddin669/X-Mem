/* The MIT License (MIT)
 *
 * Copyright (c) 2014 Microsoft
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file
 * 
 * @brief Header file for the LatencyBenchmark class.
 */

#ifndef __LATENCY_BENCHMARK_H
#define __LATENCY_BENCHMARK_H

//Headers
#include <Benchmark.h>
#include <common.h>

//Libraries
#include <cstdint>
#include <string>

namespace xmem {

	/**
	 * @brief A type of benchmark that measures unloaded memory latency via random pointer chasing.
	 */
	class LatencyBenchmark : public Benchmark {
	public:
		
		/**
		 * @brief Constructor. Parameters are passed directly to the Benchmark constructor. See Benchmark class documentation for parameter semantics.
		 */
		LatencyBenchmark(
			void* mem_array,
			size_t len,
			uint32_t iterations,
#ifdef USE_SIZE_BASED_BENCHMARKS
			uint64_t passes_per_iteration,
#endif
			uint32_t num_worker_threads,
			uint32_t mem_node,
			uint32_t cpu_node,
			pattern_mode_t pattern_mode,
			rw_mode_t rw_mode,
			chunk_size_t chunk_size,
			int64_t stride_size,
			std::vector<PowerReader*> dram_power_readers,
			std::string name
		);
		
		/**
		 * @brief Destructor.
		 */
		virtual ~LatencyBenchmark() {}

		/**
		 * @brief Get the average load throughput in MB/sec that was imposed on the latency measurement during the given iteration.
		 * @brief iter The iteration of interest.
		 * @returns The average throughput in MB/sec.
		 */
		double getLoadMetricOnIter(uint32_t iter) const;		
		
		/**
		 * @brief Get the overall average load throughput in MB/sec that was imposed on the latency measurement.
		 * @returns The average throughput in MB/sec.
		 */
		double getAvgLoadMetric() const;		
		
		/**
		 * @brief Reports benchmark configuration details to the console.
		 */
		virtual void report_benchmark_info() const;

		/**
		 * @brief Reports results to the console.
		 */
		virtual void report_results() const;

	protected:
		virtual bool _run_core();

	private:
		std::vector<double> __loadMetricOnIter; /**< Load metrics for each iteration of the benchmark. This is in MB/s. */
		double __averageLoadMetric; /**< The average load throughput in MB/sec that was imposed on the latency measurement. */	
	};
};

#endif
