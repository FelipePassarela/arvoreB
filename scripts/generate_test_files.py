import random
from pathlib import Path


def generate_test_file(
        test_dir: Path, 
        case_number: int, 
        order: int, 
        num_ops: int,
        remove_op: bool = True
    ) -> tuple[Path, Path]:
    """
    Generates test files and expected output for the B-tree.
    
    Args:
        test_dir: Base directory for test
        case_number: Test case numberr
        order: B-tree order
        num_ops: Number of operations
        remove_op: Whether to generate with remove operation. Default to True.
    
    Returns:
        Tuple with paths of the test file and output file
    """
    operations: list[str] = []
    search_result: list[str] = []
    inserted_pairs = set()

    input_dir = test_dir / "input_gerados"
    output_dir = test_dir / "output_gerados"
    input_dir.mkdir(parents=True, exist_ok=True)
    output_dir.mkdir(parents=True, exist_ok=True)

    test_file = input_dir / f"caso_teste_{case_number}.txt"
    output_file = output_dir / f"caso_teste_{case_number}_output.txt"

    ops_probas = {"I": 0.7, "R": 0.1, "B": 0.2} if remove_op else  {"I": 0.7, "B": 0.3}
    ops_types = list(ops_probas.keys())

    assert sum(ops_probas.values()) == 1.0, "Probabilidades não somam 1.0"

    for _ in range(num_ops):
        choosen_op = random.choices(
            ops_types, 
            weights=[ops_probas[op] for op in ops_types],
            k=1
        )[0]

        key, value = random.sample(range(1, num_ops), 2)

        match choosen_op:
            case "I":
                inserted_pairs.add(key)
                operations.append(f"I {key}, {value}")
            case "R":
                inserted_pairs.discard((key, value))
                operations.append(f"R {key}")
            case "B":
                search_result.append(
                    "O REGISTRO ESTA NA ARVORE!" if key in inserted_pairs 
                    else "O REGISTRO NAO ESTA NA ARVORE!")
                operations.append(f"B {key}")

    test_file.write_text(
        f"{order}\n"
        f"{len(operations)}\n"
        f"{chr(10).join(operations)}\n")    
    output_content = chr(10).join(search_result) + chr(10) if search_result else ""
    output_file.write_text(output_content)
    
    return test_file, output_file


def main():
    n_samples, max_ops = 20, 20
    remove_op = False
    
    base_dir = Path(__file__).parent.parent / "test"
    test_configs = [
        (i, random.randint(3, 25), random.randint(5, max_ops))
        for i in range(1, n_samples + 1)
    ]

    print(f"Generating {n_samples} test cases...")
    for case_num, order, num_ops in test_configs:
        test_file, output_file = generate_test_file(base_dir, case_num, order, num_ops, remove_op=remove_op)
        print(f"Input: {test_file.relative_to(base_dir)}, "
              f"Output: {output_file.relative_to(base_dir)}")


if __name__ == "__main__":
    main()