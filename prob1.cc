#include <mpi.h>
#include <cstdlib>
#include <cmath>

static constexpr std::uint32_t N = 1000;

int main (int argc, char** argv)
{
	std::array<int, N> set;
	int rank_, nop_;
	int sum = 0;
	int temp = 0;
	
	for (auto& i : set) {
		i = std::round(rand());
// 		std::cerr << i << std::endl;
	}
	
	try {
		auto ec = MPI_Init (&argc, &argv);
		if (ec != MPI_SUCCESS) throw ec;
		std::cout << "Program Started" << std::endl;
	}
	
	catch (int ec) {
		MPI_Abort (MPI_COMM_WORLD, ec);
		std::cout << "MPI_Init Failed with error code : " << ec << std::endl
				  << "Aborting!" << std::endl;
	}
	
	MPI_Comm_size (MPI_COMM_WORLD, &nop_);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank_);
	
	
	if (rank_ != 0) {
		MPI_Send (&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
// 		std::cerr << rank_ << ": Sent" << std::endl;
	}
	
	if (rank_ == 0) {
		for (int i = 1; i < nop_; ++i) {
// 			std::cerr << "Waiting Receive of : " << i << std::endl;
			MPI_Recv (&temp,
					  1,
					  MPI_INT,
					  i,
					  0,
					  MPI_COMM_WORLD,
					  MPI_STATUS_IGNORE);
// 			std::cerr << i << ":Received" << std::endl;
			sum += temp;
		}
	}
	
	if (rank_ == 0) std::cerr << sum << std::endl;
	
	MPI_Finalize();
}