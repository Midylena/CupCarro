package com.mechachieve.cupcarro;

import java.util.Collection;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.http.ResponseEntity;


public interface HistoricoDaoCupCarro extends JpaRepository<HistoricoCupCarro, Long>{
	
	@Query(value = "select * from historico_cup_carro where id = (select max(id) from historico_cup_carro);"
			+ "", nativeQuery = true)
	Collection<HistoricoCupCarro> hist();
	
}
