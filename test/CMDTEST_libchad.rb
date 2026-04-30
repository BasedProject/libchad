class CMDTEST_example < Cmdtest::Testcase
  def setup
    import_file "test/compiles.c", "compiles.c"
  end

  def test_compiles
    cmd "gcc compiles.c" do
      created_files "a.out"
    end
  end
end
